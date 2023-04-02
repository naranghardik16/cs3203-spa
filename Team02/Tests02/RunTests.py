import os
import glob
import sys
import time
from collections import Counter

"""
This code took reference from https://github.com/wn/toy-static-analyzer/blob/master/autotester_ci.py
"""

class Runner:
    def __init__(self):
        self.WINDOWS_OS_NAME = 'nt'
        self.MAC_OS_NAME = 'posix'
        self.SUCCESS_EXIT_CODE = 0
        self.FAILURE_CLOSING_TAG = '</failed>'
        self.SUCCESS_TAG = '<passed/>'
        self.OUTPUT_DIRECTORY = self.MakePathSuitableForOS(os.getcwd() + "\\Result")
        self.TOTAL_TESTS = 0
        self.TOTAL_PASSED_TESTS = 0
        self.TOTAL_FAILED_TESTS = 0

    def MakePathSuitableForOS(self, command):
        if os.name == self.WINDOWS_OS_NAME:
            command = command.replace('/', '\\')
        if os.name == self.MAC_OS_NAME:
            command = command.replace('\\', '/')
        return command

    def FindAutotesterExecutablePath(self):
        results = list()
        file_name = 'autotester.exe' if os.name == self.WINDOWS_OS_NAME else 'autotester'
        for root, dirs, files in os.walk(os.path.dirname(os.getcwd())):
            if file_name in files:
                results.append(os.path.join(root, file_name))

        if len(results) == 0:
            raise Exception(f"Unable to find {file_name} in `Code02/` folder")

        # defaulting to return the first file in the possible results
        return results[0]

    def MakeResultDirectory(self):
        does_exist = os.path.exists(self.OUTPUT_DIRECTORY)
        if not does_exist:
            os.makedirs(self.OUTPUT_DIRECTORY)

    def GetAutotesterParameterList(self, folder_to_test_in):
        current_directory = os.getcwd()
        test_name_list = glob.glob(current_directory + f"/{folder_to_test_in}/*/*.txt")
        source_test_name_list = list(filter(lambda filename: filename.endswith("source.txt"), test_name_list))
        query_test_name_list = list(filter(lambda filename: filename.endswith("queries.txt"), test_name_list))

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
            x = backslash_char if os.name == self.WINDOWS_OS_NAME else '/'

            test_name = source_file_name[source_file_name.rfind(x) + 1:-10]

            output_file_name = f"{self.OUTPUT_DIRECTORY}{x}{test_name}out.xml"
            autotester_parameter_list.append([source_file_name, query_file_name, output_file_name, test_name])

        return autotester_parameter_list

    """
    Taken from https://github.com/wn/toy-static-analyzer/blob/master/autotester_ci.py
    """

    def check_output_xml(self, output_xml):
        if not os.path.exists(output_xml):
            return "\n"
        with open(output_xml) as f:
            output = f.read()
            text_chunks = Counter(output.split())
            passed_test_cases = text_chunks[self.SUCCESS_TAG]
            failed_test_cases = text_chunks[self.FAILURE_CLOSING_TAG]
            test_summary = f'\nTest passed:{passed_test_cases}\nTest failed:{failed_test_cases}'
            self.TOTAL_TESTS += (passed_test_cases + failed_test_cases)
            self.TOTAL_PASSED_TESTS += passed_test_cases
            self.TOTAL_FAILED_TESTS += failed_test_cases
        return test_summary + "\n"

    def ExecuteAutotester(self, autotester_filepath, autotester_param, redirect_output):
        source_filepath = autotester_param[0]
        query_filepath = autotester_param[1]
        output_xml_filepath = autotester_param[2]
        test_name = autotester_param[3]

        command = f'{autotester_filepath} {source_filepath} {query_filepath} {output_xml_filepath}'
        command = self.MakePathSuitableForOS(command)

        if redirect_output:
            exit_code = os.system(command + "> LOG.txt")
        else:
            exit_code = os.system(command)

        if exit_code != self.SUCCESS_EXIT_CODE:
            test_summary = f'Autotester execution failed for {test_name} with exit code: {exit_code}'

        test_summary = f"Autotester run completed for {test_name} with output {self.check_output_xml(output_xml_filepath)}"
        return test_summary

    def Execute(self, folder_to_test_in, redirect_output):
        autotester_file_path = self.FindAutotesterExecutablePath()
        autotester_param_list = self.GetAutotesterParameterList(folder_to_test_in)
        self.MakeResultDirectory()

        test_report = ""
        for param in autotester_param_list:
            try:
                test_summary = self.ExecuteAutotester(autotester_file_path, param, redirect_output)
                test_report += "\n" + test_summary
            except Exception as e:
                print(str(e))
                continue

        # with open(self.log_file, 'a') as f:
        #     f.write(test_report)
        #     f.write("\n")
        #     f.write(f"Test statistics:\n")
        #     f.write(f"Total no. of passed test cases: {self.TOTAL_PASSED_TESTS}\n")
        #     f.write(f"Total no. of failed test cases: {self.TOTAL_FAILED_TESTS}\n")
        #     f.write(f"Total no. of test cases: {self.TOTAL_TESTS}\n")

        print(test_report)

        copy_command = "cp"
        if os.name == self.WINDOWS_OS_NAME:
            copy_command = "copy"
        move_xsl_file_to_results = self.MakePathSuitableForOS(copy_command + " analysis.xsl ./Result")

        os.system(move_xsl_file_to_results)


if __name__ == "__main__":
    start_time = time.time()
    runner = Runner()
    runner.Execute("Milestone1", True)
    runner.Execute("Milestone2", True)
    runner.Execute("Milestone3", True)

    print(f"Test statistics:")
    print(f"Total no. of passed test cases: {runner.TOTAL_PASSED_TESTS}")
    print(f"Total no. of failed test cases: {runner.TOTAL_FAILED_TESTS}")
    print(f"Total no. of test cases: {runner.TOTAL_TESTS}\n")

    print(f"Total time taken: {time.time() - start_time:.4f} second(s)")

    if runner.TOTAL_FAILED_TESTS > 0:
        raise Exception("Not everything is passing!")

    if len(sys.argv) != 2:
        start_python_host_command = "python -m http.server 8000"
        os.system(start_python_host_command)
