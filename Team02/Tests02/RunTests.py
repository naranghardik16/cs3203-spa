import os
import glob
import sys
from collections import Counter
from typing import List


"""
This code took reference from https://github.com/wn/toy-static-analyzer/blob/master/autotester_ci.py
"""
def MakePathSuitableForOS(command):
    if os.name == WINDOWS_OS_NAME:
        command = command.replace('/', '\\')
    if os.name == MAC_OS_NAME:
        command = command.replace('\\', '/')
    return command


WINDOWS_OS_NAME = 'nt'
MAC_OS_NAME = 'posix'
SUCCESS_EXIT_CODE = 0
FAILURE_CLOSING_TAG = '</failed>'
SUCCESS_TAG = '<passed/>'
OUTPUT_DIRECTORY = MakePathSuitableForOS(os.getcwd() + "\\Result")


def FindAutotesterExecutablePath():
    results: List[str] = list()
    file_name = 'autotester.exe' if os.name == WINDOWS_OS_NAME else 'autotester'
    for root, dirs, files in os.walk(os.path.dirname(os.getcwd())):
        if file_name in files:
            results.append(os.path.join(root, file_name))

    if len(results) == 0:
        raise Exception(f'Unable to find {file_name} in `Code02/` folder')

    # defaulting to return the first file in the possible results
    return results[0]


def MakeResultDirectory():
    isExist = os.path.exists(OUTPUT_DIRECTORY)
    if not isExist:
        os.makedirs(OUTPUT_DIRECTORY)


def GetAutotesterParameterList(folder_to_test_in):
    current_directory = os.getcwd()
    test_name_list = glob.glob(current_directory + f"/{folder_to_test_in}/*/*.txt")
    source_test_name_list = list(filter(lambda filename : filename.endswith("source.txt"), test_name_list))
    query_test_name_list = list(filter(lambda filename : filename.endswith("queries.txt"), test_name_list))

    # each source file will have a query file with the same test name
    sorted_source_test_name_list = sorted(source_test_name_list)
    sorted_query_test_name_list = sorted(query_test_name_list)
    assert len(sorted_source_test_name_list) == len(sorted_query_test_name_list), \
        "Not every source file has a query file or vice versa"

    autotester_parameter_list = []
    for i in range(len(sorted_source_test_name_list)):
        source_file_name = sorted_source_test_name_list[i]
        query_file_name = sorted_query_test_name_list[i]

        source_test_name = source_file_name[:-10]
        query_test_name = query_file_name[:-11]
        assert source_test_name == query_test_name, \
            f"Source file name is {source_test_name} while query file name is {query_test_name}"

        backslash_char = "\\"
        x = backslash_char if os.name == WINDOWS_OS_NAME else '/'

        test_name = source_file_name[source_file_name.rfind(x)+1:-10]

        output_file_name = f"{OUTPUT_DIRECTORY}{x}{test_name}out.xml"
        autotester_parameter_list.append([source_file_name, query_file_name, output_file_name, test_name])

    return autotester_parameter_list


"""
Taken from https://github.com/wn/toy-static-analyzer/blob/master/autotester_ci.py
"""
def check_output_xml(output_xml):
    with open(output_xml) as f:
        output = f.read()
        text_chunks = Counter(output.split())
        passed_test_cases = text_chunks[SUCCESS_TAG]
        failed_test_cases = text_chunks[FAILURE_CLOSING_TAG]
        test_summary = f'\nTest passed:{passed_test_cases}\nTest failed:{failed_test_cases}'
    return test_summary


def ExecuteAutotester(autotester_filepath, autotester_param, redirect_output):
    source_filepath = autotester_param[0]
    query_filepath = autotester_param[1]
    output_xml_filepath = autotester_param[2]
    test_name = autotester_param[3]

    command = f'{autotester_filepath} {source_filepath} {query_filepath} {output_xml_filepath}'
    command = MakePathSuitableForOS(command)

    if redirect_output:
        exit_code = os.system(command + "> /dev/null 2>&1")
    else:
        exit_code = os.system(command)

    if exit_code != SUCCESS_EXIT_CODE:
        test_summary = f'Autotester execution failed for {test_name} with exit code: {exit_code}'

    test_summary = f"Autotester run completed for {test_name} with output {check_output_xml(output_xml_filepath)}"
    return test_summary


def Execute(folder_to_test_in, redirect_output):
    autotester_file_path = FindAutotesterExecutablePath()
    autotester_param_list = GetAutotesterParameterList(folder_to_test_in)
    MakeResultDirectory()

    test_report = ""
    for param in autotester_param_list:
        try:
            test_summary = ExecuteAutotester(autotester_file_path, param, redirect_output)
            test_report += "\n" + test_summary
        except Exception as e:
            print(str(e))
            continue

    print(test_report)
    copy_command = "cp"
    if os.name == WINDOWS_OS_NAME:
        copy_command = "copy"
    move_xsl_file_to_results = MakePathSuitableForOS(copy_command + " analysis.xsl ./Result")

    os.system(move_xsl_file_to_results)


if __name__ == "__main__":
    Execute("Milestone1", True)
    Execute("Milestone2", True)

    if len(sys.argv) != 2:
        start_python_host_command = "python -m http.server 8000"
        os.system(start_python_host_command)


