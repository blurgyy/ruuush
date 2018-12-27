#!/usr/bin/python3 -B
import os
import sys
import shutil
import functools
import platform
import argparse
import hashlib
import textwrap
import subprocess

import util
import languages
import languages_util
import log
import defaults

def findLanguage(program, action, quiet = False):
    if not quiet and not os.path.exists(program):
        raise PException('Cannot {0} "{1}". Program not found.', action, program)

    lprogram = program.lower()
    for language in languages.languages:
        if lprogram.endswith(language["suffix"].lower()):
            return language

    if quiet:
        return dict(compile = languages_util.noCompile, run = [])
    raise PException('Cannot {0} "{1}". Unsupported type.', action, program)

def findSuffix(program, default = None):
    for language in languages.languages:
        file = program + language["suffix"]
        if os.path.exists(file) and not os.path.isdir(file):
            return file
    if os.path.exists(program) and not os.path.isdir(program):
        return program
    return default if default else program

def programExists(program):
    return os.path.exists(findSuffix(program, "~~~"))

def loadProperties(filename):
    """
        Loads .properties file into dictionary.
        The values are separated by = symbol.
        Comments lines started with # symbol.
        Names and values are trimmed.
    """
    properties = dict()
    if os.path.exists(filename):
        with open(filename) as file:
            for line in file.readlines():
                if line.strip() != "" and line[0] != "#":
                    (name, value) = line.split("=", 1)
                    properties[name.strip()] = value.strip()
    return properties

def loadContestProperties(filename = "../contest.properties"):
    properties = dict(defaults.contestProperties)
    properties.update(loadProperties(filename))
    return properties

class Problem(dict):
    def __init__(self, properties):
        super().__init__(**properties)
        self.id = properties["id"]
        self.name = properties["name"]
        self.alias = properties["alias"]

        self.solution = properties["solution"]

        self.timeLimit = properties["timelimit"]
        self.memoryLimit = properties["memorylimit"]

        self.input = properties["input"]
        self.output = properties["output"]
        self.inputFile = properties["input"] if properties["input"] != "*" else "input.__"
        self.outputFile = properties["output"] if properties["output"] != "*" else "output.__"
        self.answerFile = properties["answer"] if properties["answer"] != "*" else "answer.__"

        self.testsDir = properties["testsdir"]
        self.tests = properties["tests"]
        self._tests_format = "{{:0{}d}}".format(len(self.tests))

    def test(self, no):
        return Test(self, self._tests_format.format(int(no)))

    def allTests(self):
        return [self.test(x) for x in range(1, 10 ** len(self["tests"]))]

    def existingTests(self):
        return [test for test in self.allTests() if test.inputExists()]


def loadProblemProperties(id = None, filename="problem.properties"):
    contest = loadContestProperties()
    if not id:
        id = os.path.basename(os.getcwd())
    properties = dict(id=id, testset="??", solution="??")
    properties.update(loadProperties(filename))
    id = properties["id"]
    base = dict(
        input = id + ".in",
        output = id + ".out",
        answer = id + ".ans",
        log = id + ".log",
        source = id,
        checker = properties["testset"],
        alias = id[0].upper(),
        name ="??",
        tests = "##",
        testsdir = contest["testsdir"],
        timelimit = contest["timelimit"],
        memorylimit = contest["memorylimit"],
    )
    base["short-id"] = id[0]
    base.update(properties)
    return Problem(base)

class PException(Exception):
    def __init__(self, message, *args):
        self.message = message.format(*args)

class Test:
    def __init__(self, problem, name):
        self.problem = problem
        self.name = name
        self.input = util.join(problem.testsDir, name)
        self.answer = util.join(problem.testsDir, name + ".a")

    def inputExists(self):
        return os.path.exists(self.input)

    def answerExists(self):
        return os.path.exists(self.answer)

    def logAction(self, action, message, logger):
        logger("{} on problem {} test {}", message, self.problem.id, self.name)
        util.appendFile("t-{}.log".format(action), "{} {}", self.name, message)

    def verdict(self, short, full, exitcode):
        return (short + " on test " + self.name, full + " on test " + self.name, self.name, exitcode)

    def run(self, options, action, solution):
        log.info("Running {} on problem {} test {}.", solution, self.problem.id, self.name)
        shutil.copyfile(self.input, self.problem.inputFile)
        util.removeFiles(self.problem.outputFile)

        oldTimeLimit = options.time_limit
        options.time_limit = options.time_limit or self.problem.timeLimit
        oldMemoryLimit = options.memory_limit
        options.memory_limit = options.memory_limit or self.problem.memoryLimit
        exitcode = time(
            options,
            solution,
            stdin = None if self.problem.input != "*" else self.problem.inputFile,
            stdout = None if self.problem.output != "*" else self.problem.outputFile
        )
        options.time_limit = oldTimeLimit
        options.memory_limit = oldMemoryLimit
        if exitcode:
            s = " (" + runExitCodes[exitcode][1] + ")" if exitcode in runExitCodes else ""
            self.logAction(action, "Failed to run with exitcode 0x{:X}{}".format(exitcode, s), log.warning)
            return self.verdict(
                runExitCodes[exitcode][0] if exitcode in runExitCodes else "RE {}".format(exitcode),
                runExitCodes[exitcode][1] if exitcode in runExitCodes else "Exit code {}".format(exitcode),
                exitcode
            )
        return None

    def check(self, action):
        if not self.answerExists():
            self.logAction(action, "Answer file is not found", log.warning)
            return 1

        with open("check.__", "w") as stdout:
            exitcode = run("Check", self.problem.inputFile, self.problem.outputFile, self.answer, stdout=stdout)
            output = ' '.join([line.strip() for line in util.readLines("check.__")])
            print(output)
            if exitcode:
                full = checkerExitCodes[exitcode][1] if exitcode in checkerExitCodes else "?? {}".format(exitcode)
                short = checkerExitCodes[exitcode][0] if exitcode in checkerExitCodes else "?? {}".format(exitcode)
                self.logAction(action, "Check has not accepted solution: {}\n{}".format(full, output), log.warning)
                return self.verdict(short, full, exitcode)
        self.logAction(action, "ok", log.info)
        return None

runExitCodes = {
    0xFFFFFFFF: ("TL", "Time limit exceeded"),
    0xFFFFFFFE: ("ML", "Memory limit exceeded"),
    0xFFFFFFFD: ("IL", "Idleness limit exceeded"),
    0xFFFFFFFC: ("RE", "Runtime error"),
    0xFFFFFFFB: ("SV", "Security violation"),
    0x80000000: ("FAIL", "FAIL")
}

checkerExitCodes = {
    0: ("OK", "Accepted"),
    1: ("WA", "Wrong answer"),
    2: ("PE", "Presentation error"),
    3: ("FAIL", "FAIL"),
    4: ("PC", "Partial correct")
}

def executeAndLog(*command, **kwargs):
    util.appendFile("t-run.log", "--- {}", " ".join(command))
    exitcode = util.execute(*command, **kwargs)
    util.concatFiles("t-run.log", "t-run.out", "t-run.err")
    return exitcode

def runCommand(program, args = []):
    program = findSuffix(program)
    return findLanguage(program, "run")["run"](program, list(args))

def recursiveDirs():
    return [
        file for file in os.listdir()
        if os.path.isdir(file)
        if not file.startswith("_")
        if not file.startswith(".")
    ]

def recursive(f, test):
    def rec(options):
        if test():
            return f(options)
        log.glob("Scanning {0}", os.getcwd())
        for file in recursiveDirs():
            os.chdir(file)
            exitcode = rec(options)
            os.chdir("..")
            if exitcode:
                return exitcode
        return 0
    return rec

def recWrapper(options, action, description, type, id, f):
    log.glob('{} for {} {} in {}', description, type, id, os.getcwd())
    try:
        exitcode = f(options)
        if exitcode:
            log.warning("{} FAILED FOR {} {}. See t-{}.log.", action.upper(), type.upper(), id, action)
        else:
            log.glob("{} SUCCESSFUL FOR {} {}.", action.upper(), type.upper(), id)
    except PException as e:
        raise PException('{} FAILED FOR {} {}: {}', action.upper(), type.upper(), id, e.message)

def recProblem(action, description, f):
    def wrapper(options):
        problem = loadProblemProperties()
        recWrapper(options, action, description, 'problem', '"' + problem.id + '"', f)

    return recursive(wrapper, lambda : os.path.exists(defaults.testsDir) or programExists("Tests") or os.path.exists("problem.properties"))

def recContest(action, description, f):
    def wrapper(options):
        contest = loadContestProperties("contest.properties")
        recWrapper(options, action, description, 'contest', '"' + contest['name-1'] + ", " + contest['name-2'] + '"', f)

    return recursive(wrapper, lambda : os.path.exists("contest.properties"))

def recContestProblem(action, description, contest_f, problem_f):
    def wrapper(options):
        return (recContest(action, description, contest_f)(options)
            or recProblem(action, description, problem_f)(options))
    return wrapper

def runAction(options, action, testAction):
    problem = loadProblemProperties()
    util.removeFiles("t-{}.log".format(action), "t-run.log", "t-run.err", "t-run.out", "run.dat")

    make("Check")
    make("Interact", quiet = True)

    def resolveSolution(solution, problem):
        if solution == "*": return resolveSolution(problem.solution, problem)
        if os.path.exists(solution): return solution
        return problem.id + "_" + solution

    solution = findSuffix(resolveSolution(options.solution, problem))
    make(solution)

    stopOnFirstError = options.stop_on_first_error or defaults.stopOnFirstError
    tests = map(lambda no: problem.test(no), options.test) if options.test else problem.existingTests()
    if not tests:
        raise PException("No tests found")

    verdict = None
    for test in tests:
        result = testAction(options, test, solution)
        verdict = verdict or result
        if result and stopOnFirstError: 
            break
    verd = verdict or ("OK", "Accepted", 0, 0)

    if os.path.exists("run.dat"):
        stats = loadProperties("run.dat")
        time = stats["max.timeConsumed"]
        memory = int(stats["max.memoryConsumed"])
        log.info("VERDICT IS: {}", verd[1])
        log.info("MAX TIME IS: {}ms", time)
        log.info("MAX MEMORY IS: {:,}B", memory)
        util.appendFile(problem["log"], "{:<7}\t{:<31}\t{:<15}\t{:>5}ms\t{:>5}MB\t{}", 
            action,
            solution,
            verd[0],
            time,
            round(memory / 1024 / 1024),
            "tests = [" + " ".join(options.test) + "]" if options.test else ""
        )
    if defaults.removeInputAndOutput:
        util.removeFiles(problem.inputFile, problem.outputFile, problem.answerFile)

    return verdict

def findCheckerAndTests():
    problem = loadProblemProperties()
    def fail(message, *args):
        raise PException("Must build first, {}".format(message), *args)

    def find(name, quiet = False):
        for file in [name + ".jar", name + ".exe"]:
            if os.path.exists(file):
                log.info("{} found", file)
                return file
        if not quiet:
            fail(name + ".exe/jar is missing.")

    def checkTest(test):
        if not test.inputExists() and programExists(util.join(problem.testsDir, "do" + test.name)):
            fail("test {} not generated.", test.name)
        if not test.answerExists() and test.inputExists():
            fail("answer is missing for test {}.", test.name)
        return test.inputExists()

    tests = list(filter(checkTest, problem.allTests()))
    for actual, expected in zip(tests, problem.allTests()):
        if actual.name != expected.name:
            raise PException("Noncontiguous test set. Test {} is missing", expected.name)
    if not tests:
        fail("no tests found")
    log.info("{} tests found", len(tests))

    return find("Check"), find("Interact", quiet = True), tests

class HelpFormatter(argparse.ArgumentDefaultsHelpFormatter):
    def _fill_text(self, text, width, indent):
        return "\n".join([
            textwrap.fill(self._whitespace_matcher.sub(' ', paragraph).strip(), width, initial_indent=indent, subsequent_indent=indent)
            for paragraph in text.split("\\n")
        ])

header = textwrap.dedent("""
    Problem build tool.\\n
    (C) Georgiy Korneev, 2012\\n
    Based on and compatible with t.cmd by Roman Elizarov et al.
""")
parser = argparse.ArgumentParser(
    prog = "p",
    description = header,
    epilog = """
        Type "p SUBCOMMAND --help" for help on a specific subcommand.
        \\n\\n
        PROGRAMS
        \\n\\n
        Some subcommands (e.g. "build" and "check") takes program name
        as an argument. This argument could specify either a full name of
        the program or a program name with suffix omitted. In the former
        case, the program should have one of supported suffixes
        ({suffixes}). If the suffix is omitted, the first suitable suffix
        is used.
        \\n\\n
        For example, if there are both "Tests.java" and "Tests.class" files
        in the current directory, then one can specify
        programs "Tests.java", "Tests.class" and "Tests". In
        the latter case, the "Tests" will be expanded to "Tests.java"
        (as .java comes before .class in supported suffixes list).
        \\n\\n
        DIRECTORY STRUCTURE
        \\n\\n
        Problem build tool assumes that each directory with problem
        has at least one of the following items:
        "tests" subdirectory, "Tests" program or "problem.properties" file.
        \\n\\n
        Tests are named 01, 02, 03,..., 99 (this may be overridden via
        "tests" problem property). Tests are generated using "build" subcommand.
        All other subcommand expects that tests are already build.
        Answer files are placed into "XX.a" files after build. They are
        generated by running a specified model solution.
        \\n\\n
        Some subcommands (e.g. "build" and "check") are problem-recursive.
        They are marked with [p] in list of subcommands. Such kind of
        subcommands recursively scan subdirectories in search for problem
        directories and performs subcommand for each problem found.
        \\n\\n
        Some subcommands (e.g. "xml" and "pcms") are both problem-recursive
        and contest-recursive (marked with [cp]). Their recursively scans
        current directory for both problem and contest directories, and
        performs corresponding tasks in them. If contest directory is
        found, the subdirectories are scanned for problem directories.
        Contest directory is identified by the presence of the
        "contest.properties" file.
        \\n\\n
        SPECIFYING SOLUTION
        \\n\\n
        "Build" and "check" subcommands accept solution as an argument.
        Source or executable file with solution may be explicitly
        specified (see PROGRAMS section for a list of supported extensions).
        For example, "p build solution.java" will build answer files using
        "solution.java".
        \\n\\n
        Suffix for the solution name may be specified instead. In this
        case, problem id and underscore are appended before the specified
        suffix. For example, "p build gk.java" for problem "box" will
        generate answers using "box_gk.java". Extension may be omitted in
        the suffix, so the last command may be shortened to just "p build
        gk".
        \\n\\n
        Combined with recursive behavior one can run it in the top-level
        directory to build all problems with solutions that have "gk"
        suffix. If solution is omitted entirely or specified as "*",
        the "solution" problem property is used.
        \\n\\n
        PROBLEM PROPERTIES
        \\n\\n
        Problem properties are specified in "problem.properties" file in
        the problem directory. Properties are specified using "key=value"
        format, on property per line. Empty lines are ignored, as well as
        lines starting with '#' character.
        \\n\\n
        Supported properties are:
        \\n* id -- problem id (defaults to problem directory name)
        \\n* input -- input file name (defaults to "<id>.in")
        \\n* output -- output file name (defaults to "<id>.out")
        \\n* answer -- output file name (defaults to "<id>.ans")
        \\n* tests -- test files name pattern (defaults to "##")
        \\n* testset -- test set author's initials (defaults to "??")
        \\n* solution -- model solution author's initials (defaults to "??")
        \\n* checker -- checker author initials (defaults to test set author)
        \\n* source -- model solution (defaults to "<id>")
        \\n* short_id -- short problem id (defaults to first letter of <id>)
        \\n* alias -- problem alias (defaults to capitalized short_id)
        \\n* name -- problem name (defaults to "??")
        \\n* testsdir -- name of the directory containing tests (inherited from contest)
        \\n\\n
        CONTEST PROPERTIES
        \\n\\n
        Contest properties are specified in "contest.properties" file in
        the same format as problem properties.
        \\n\\n
        Supported properties are:
        \\n* name-1 -- first line of the contest name
        \\n* name-2 -- second line of the contest name
        \\n* location -- contest location
        \\n* date -- contest date
        \\n* timelimit -- default problem time limit
        \\n* memorylimit -- default problem memory limit
        \\n* problem-prefix -- PCMS problem id prefix
        \\n\\n
        CONFIGURATION
        \\n\\n
        Default option and property values, are specified in "defaults.py".\\n
        Supported languages, corresponding compile and run commands
        are specified in "languages.py".
        \\n\\n
        FEEDBACK
        \\n\\n
        Please report all bugs and suggestions for this tool to Georgiy Korneev
        using email kgeorgiy@rain.ifmo.ru
    """.format(suffixes = ", ".join([l["suffix"] for l in languages.languages])),
    formatter_class = HelpFormatter
)
parser.add_argument("-v", "--verbose", action="store_true", help="print debug output")
parser.add_argument("-d", "--directory", dest="dir", action="store", default="current directory", help="execute commands in the specified directory")
subparsers = parser.add_subparsers(
    title = 'available subcommands',
    description = '',
    help = 'DESCRIPTION',
    metavar = "SUBCOMMAND"
)
parser.add_argument('+', metavar="+ SUBCOMMAND", nargs = "*", help = 'More subcommands')

def make(*programs, quiet = False):
    for program in programs:
        program = findSuffix(program)
        log.debug("Making {}", program)

        language = findLanguage(program, "make", quiet)
        if not language["compile"]:
            raise PException('Cannot make "{0}". {1} are not programs.', program, language.description)

        exitcode = language["compile"](program)
        if exitcode != 0:
            raise PException('Cannot make "{0}". Exitcode={1}', program, exitcode)
    return 0

def makeDescription():
    langs = languages.languages
    suffixes = [l["suffix"] for l in langs]
    scripts = [l["suffix"] for l in langs if l["compile"] == languages_util.noCompile]
    return """
        Makes the specified programs files. Supported extensions are: {}.
        In the later cases ({}) make just silently quits.

        Extension may be omitted. In this case make will try to find the
        file by attaching extensions in the order they are listed above.
        For example, "t make solution" will compile "solution.java" file
        (if it exits) using Java.
    """.format(", ".join(suffixes), ", ".join(scripts))

parser_make = subparsers.add_parser(
    'make',
    aliases = 'm',
    help = 'Makes programs',
    description = makeDescription(),
    formatter_class = HelpFormatter
)
parser_make.add_argument('programs', metavar='PROGRAM', nargs='+', help = 'program to make')
parser_make.set_defaults(func = lambda options: make(*options.programs))

def run(program, *args, **kwargs):
    return executeAndLog(*runCommand(program, list(args)), **kwargs)

parser_run = subparsers.add_parser(
    'run',
    aliases = 'r',
    help = 'Runs program',
    description = """
        Runs the specified program (source or executable file). It assumes
        that the source file is already compiled using "make" subcommand
        and uses the corresponding command to run it. For example, "t run
        solution.java" will actually run "java solution", while "t run
        solution.cpp" will actually run "solution.exe". Extension may be
        omitted just like in "make" subcommand.
    """,
    formatter_class = HelpFormatter
)
parser_run.add_argument('program', metavar='PROGRAM', help = 'program to run')
parser_run.add_argument('args', metavar='ARG', nargs='*', help = 'program arguments')
parser_run.set_defaults(func = lambda options: run(options.program, *options.args))

def timeInteract(command, interact, timeLimit):
    s2ir, s2iw = os.pipe()
    try:
        i2sr, i2sw = os.pipe()
        try:
            with subprocess.Popen(command, stdin=i2sr, stdout=s2iw) as solution:
                with subprocess.Popen(interact, stdin=s2ir, stdout=i2sw) as interact:
                    import threading
                    def start(process):
                        thread = threading.Thread(target = (lambda : process.communicate()))
                        thread.start()
                        return thread

                    solutionThread = start(solution)
                    interactThread = start(interact)

                    timeout = float(timeLimit[:-1])
                    solutionThread.join(timeout)
                    def stop(process, thread):
                        if not thread.is_alive():
                            return False
                        thread.join(timeout)
                        if thread.is_alive():
                            process.terminate()
                            thread.join()
                        return True

                    solutionStopped = stop(solution, solutionThread)
                    stop(interact, interactThread)
                    if solutionStopped:
                        return 0xffffffff
                    if interact.returncode == 10:
                        return 0xfffffffa
                    return solution.returncode or interact.returncode
        finally:
            os.close(i2sr)
            os.close(i2sw)
    finally:
        os.close(s2ir)
        os.close(s2iw)


def time(options, program, *args, stdin = None, stdout = None):
    command = runCommand(program, args)
    log.debug('Running "{}"', ' '.join(command))

    bits = 64 if defaults.allow64bits and platform.machine() == "AMD64" else 32

    interact = runCommand("Interact") if programExists("Interact") else None
    timeLimit = options.time_limit or defaults.timelimit
    memoryLimit = options.memory_limit or defaults.memorylimit

    wrapper = util.relpath("p\\run{}.exe".format(bits))

    if os.path.exists(wrapper):
        return executeAndLog(*
            [wrapper] + defaults.runOptions +
            ["-t", timeLimit] +
            ["-m", memoryLimit] +
            ["" if options.output else "-qs"] +
            (["-i", stdin] if stdin else []) +
            (["-o", stdout] if stdout else []) +
            (["-I", "=" + " ".join(interact) + "="] if interact else []) +
            command
        )
    elif interact:
        return timeInteract(command, interact, timeLimit)
    else:
        inf = open(stdin, "rb") if stdin else None
        ouf = open(stdout, "wb") if stdout else None
        try:
            return executeAndLog(*command, timeout = float(timeLimit[:-1]), stdin = inf, stdout = ouf)
        except subprocess.TimeoutExpired as e:
            print(e)
            return 0xffffffff
        finally:
            if inf: inf.close()
            if ouf: ouf.close()

parser_time_parent = argparse.ArgumentParser(add_help = False)
parser_time_parent.add_argument("-o", "--output", action="store_true", help = 'show output of runXX wrapper')
parser_time_parent.add_argument("-t", "--time-limit", help = 'time limit')
parser_time_parent.add_argument("-m", "--memory-limit", help = 'memory limit')

parser_time = subparsers.add_parser(
    'time',
    aliases = 't',
    help = 'Runs program using "runXX.exe"',
    description = """
        Works like run subcommand, but execution is wrapped into
        "runXX.exe", if the corresponding wrapper file exists
        in "{}" directory), otherwise
        run is performed directly.
        \\n\\n
        For interactive problems "Interact" is also executed.
    """.format(util.relpath("p")),
    parents = [parser_time_parent],
    formatter_class = HelpFormatter
)
parser_time.add_argument('program', metavar='PROGRAM', help = 'program to run')
parser_time.add_argument('args', metavar='ARG', nargs='*', help = 'program arguments')
parser_time.set_defaults(func = lambda options: time(options, options.program, *options.args))

def problem_check(options):
    def checkTest(options, test, solution):
        return test.run(options, "check", solution) or test.check("check")

    return runAction(options, "check", checkTest)

parser_check_parent = argparse.ArgumentParser(add_help = False, parents = [parser_time_parent])
parser_check_parent.add_argument('-s', '--stop-on-first-error', action = 'store_true', help = 'stops checking after first test failed')
parser_check = subparsers.add_parser(
    'check',
    aliases = 'c',
    help = 'Check solution [p]',
    description = """
        Checks specified solution. It creates "t-check.log" file where outcome
        for each test is listed (one test on a line). Checker program shall be
        named "check" and shall accept "input" "output" and "answer" arguments in this
        order. Works with all available tests unless the list of tests is
        explicitly specified.
    """,
    parents = [parser_check_parent],
    formatter_class = HelpFormatter
)
parser_check.add_argument('solution', metavar='SOLUTION', nargs='?', help = 'solution to check', default = '*')
parser_check.add_argument('test', metavar='TEST', nargs='*', help = 'test to check on')
parser_check.set_defaults(func = recProblem("check", "Checking problem", problem_check))

def problem_build(options):
    def makeAndRun(program, **kwargs):
        make(program)
        exitcode = run(program, **kwargs)
        if exitcode:
            raise PException("Error running {}. Exitcode={}", program, exitcode)

    def buildTest(options, test, solution):
        exitcode = test.run(options, "build", solution)
        if exitcode:
            return exitcode

        shutil.copyfile(test.problem.outputFile, test.answer)
        return test.check("build")

    problem = loadProblemProperties()
    log.info("Generating tests")
    util.removeFiles(*[test.answer for test in problem.allTests()])
    if programExists("Tests"):
        util.removeDirs(problem.testsDir)
        os.mkdir(problem.testsDir)
        makeAndRun("Tests")
    else:
        os.chdir(problem.testsDir)
        if programExists("doall"):
            util.removeFiles(*[util.join("../", test.input) for test in problem.allTests()])
            makeAndRun("doall")
        else:
            for test in problem.allTests():
                if programExists("do" + test.name):
                    util.removeFiles(test.answer)
                    with open(util.join("..", test.input), "wb") as testFile:
                        makeAndRun("do" + test.name, stdout = testFile)
        os.chdir("..")

    def hashFile(filename):
        with open(filename, "rb") as file:
            return hashlib.sha256(file.read()).hexdigest()

    if options.generate_hashes:
        log.info("Generating test hashes")
        with open("tests.sha256", "wb") as file:
            for test in problem.existingTests():
                log.debug("Generating hash for test {}", test.name)
                file.write((hashFile(test.input) + " " + test.input).encode("utf8"))
                file.write(b"\n")
    elif os.path.exists("tests.sha256"):
        log.info("Verifying test hashes")
        hashes = dict()
        for line in util.readLines("tests.sha256"):
            hash, file = line.strip().split(" ")
            hashes[file] = hash
        for test in problem.existingTests():
            log.debug("Verifying hash for test file {}", test.input)
            if not test.input in hashes:
                raise PException('New test file found "{}"', test.input)
            if hashFile(test.input) != hashes[test.input]:
                raise PException('Hash mismatch for test file "{}"', test.input)
            del hashes[test.input]
        if len(hashes) != 0:
            raise PException('Test file "{}" missing', list(hashes.keys())[0])
    return runAction(options, "build", buildTest)

parser_build = subparsers.add_parser(
    'build',
    aliases = 'b',
    help = 'Build test and answer files [p]',
    description = """
        Builds test and answer files. It creates "t-build.log" file
        where outcome for each test is listed (one test on a line). If
        solution is not found, then answer files are not generated.
        \\n\\n
        Tests are generated using test generators. If program "tests" is
        present in the problem directory, then it is run and it must generate
        ALL test files. If program "doall" is present in the "tests"
        subdirectory of the problem directory, then it is run and it must
        generate ALL test files. If none of the "tests" nor "doall" programs
        are present, the "doXX" generators from "tests" directory are used.
        Such generators must print tests to the console. This output
        will be redirected to the corresponding test file.
        \\n\\n
        Works for all available tests unless the the list of tests is
        explicitly specified. When tests are being built it also compiles
        checker program named "check" if it exists.
        \\n\\n
        If "tests.sha256" file exists, check test hash codes against it.
        This file could be generated using "-g" option.
    """,
    parents = [parser_check_parent],
    formatter_class = HelpFormatter
)
parser_build.add_argument('solution', metavar='SOLUTION', nargs='?', help = 'solution for generating answers', default = '*')
parser_build.add_argument('test', metavar='TEST', nargs='*', help = 'tests to generate answers for')
parser_build.add_argument('-g', '--generate-hashes', action='store_true', help = 'generate test hashes')
parser_build.set_defaults(func = recProblem("build", "Building problem", problem_build))



def contest_xml(options):
    contest = loadContestProperties("contest.properties")
    body = "\n    ".join([
        '<problem-ref id = "{short-id}" alias = "{alias}" problem-id = "{id}" name = "{name}"/>'.format(**loadProblemProperties(file, file + "/problem.properties"))
        for file in os.listdir() if os.path.isdir(file) if not file.startswith("_") and not file.startswith(".")
    ])
    util.writeFile("challenge.xml", """
<challenge
    id              = "{id}"
    name            = "{name-1}, {name-2}"
    scoring-model   = "%icpc"
    length          = "5h"

    problem-id      = "{problem-prefix}"
    xmlai-process   = "http://neerc.ifmo.ru/develop/pcms2/xmlai/default-rules.xml"
>
    {body}
</challenge>""".format(body = body, **contest)
    )
    return 0

def problem_xml(options):
    problem = loadProblemProperties()
    contest = loadContestProperties()

    timeLimit = options.time_limit if options.time_limit else problem.timeLimit
    memoryLimit = options.memory_limit if options.memory_limit else problem.memoryLimit

    util.removeFiles("problem.xml")

    prefix = options.prefix or contest["problem-prefix"]
    prefix = prefix if prefix == "" or prefix.endswith(".") else prefix + "."

    checker, interact, tests = findCheckerAndTests()
    def binary(program):
        return '<binary executable-id = "{}" file = "{}"/>'.format(
                "java.check" if program.lower() == "check.jar"
                else "java.jar" if program.lower()[-4:] == ".jar"
                else "x86.exe.win32",
                program
        )
    util.writeFile("problem.xml", """
<problem
    id      = "{id}"
    version = "1.0"
>
    <judging>
        <script type = "%icpc">
            <testset
                test-count   = "{testNumber}"
                input-href   = "{testsDir}/{tests}"
                answer-href  = "{testsDir}/{tests}.a"
                input-name   = "{input}"
                output-name  = "{output}"
                time-limit   = "{timelimit}"
                memory-limit = "{memorylimit}"
            />
            <verifier type = "%testlib">
                {checkerLine}
            </verifier>
            {interactorLine}
        </script>
    </judging>
</problem>""".format(
        id = prefix + problem.id,
        checkerLine = binary(checker),
        timelimit = timeLimit,
        memorylimit = memoryLimit,
        testNumber = len(tests),
        testsDir = problem.testsDir,
        tests = problem.tests,
        input = problem.input,
        output = problem.output,
        interactorLine = """
            <interactor type = "%simple">
                {}
            </interactor>
        """.format(binary(interact)) if interact else ""
    ))
    return 0

parser_xml = subparsers.add_parser(
    'xml',
    aliases = 'x',
    help = 'Builds "challenge.xml" and "problem.xml" [cp]',
    description = """
        Builds "challenge.xml" and "problem.xml", so that contest (problem)
        can be used with PCMS2-v2 contest management system. You must
        successfully use "build" subcommand before using xml subcommand.
        Prefix is prepended to problem identifiers (default is empty).
        Default time limit is 2s, memory limit 67108864.
    """,
    formatter_class = HelpFormatter
)
parser_xml.add_argument("-p", "--prefix", help = "problem prefix")
parser_xml.add_argument("-t", "--time-limit", help = "contest time limit (default {})".format(defaults.contestProperties["timelimit"]))
parser_xml.add_argument("-m", "--memory-limit", help = "contest memory limit (default {})".format(defaults.contestProperties["memorylimit"]))
parser_xml.set_defaults(func = recContestProblem("xml", "Building XML", contest_xml, problem_xml))



def contest_pcms(options):
    contestDir = util.relswd(options.directory)
    util.cleanDirs(contestDir)

    if not os.path.exists("challenge.xml"):
        raise PException('Must run "xml" first, challenge.xml not found')
    util.copyToDir("challenge.xml", contestDir)
    return 0

def problem_pcms(options):
    problem = loadProblemProperties()
    problemDir = util.join(util.relswd(options.directory), problem.id)
    testsDir = util.join(problemDir, problem.testsDir)

    util.cleanDirs(problemDir, testsDir)

    if not os.path.exists("problem.xml"):
        raise PException('Must run "xml" first, problem.xml not found')

    checker, interact, tests = findCheckerAndTests()
    util.copyToDir(checker, problemDir)
    if interact: util.copyToDir(interact, problemDir)

    for test in tests:
        util.copyToDir(test.input, problemDir)
        util.copyToDir(test.answer, problemDir)

    for name in ["Check", "Interact"]:
        file = findSuffix(name)
        if os.path.exists(file):
            log.info(file + " found")
            util.copyToDir(file, problemDir)

    bannerSpecial(problemDir, "Check", "Checker", "checker")
    bannerSpecial(problemDir, "Interact", "Interactor", "interact")
    banner(problemDir, languages_util.comments_xml, "problem.xml")

    return 0

parser_pcms = subparsers.add_parser(
    'pcms',
    aliases = 'p',
    help = 'Creates PCMS contest/problem directory [cp]',
    description = """
        Copies PCMS configuration files (chellenge.xml, problem.xml, tests,
        checker) to the specified directory. You must successfully use "build"
        and "xml" subcommand before using pcms subcommand.
    """,
    formatter_class = HelpFormatter
)
parser_pcms.add_argument("-d", "--directory", help = "directory to write result to")
parser_pcms.set_defaults(func = recContestProblem("pcms", "Building PCMS", contest_pcms, problem_pcms), directory = "__pcms")



def banner(problemDir, comments, file, type = None, author = None):
    contest = loadContestProperties()
    problem = loadProblemProperties()
    if type and not author:
        author = file[len(problem.id):].split(".")[0].split("_")[1]
    line = comments["begin"] + comments["line"] * 64 + comments["end"]

    def text(format, *args):
        return comments["begin"] + " " + format.format(*args).ljust(63) + comments["end"]

    def multiline(name, property):
        if not property in problem:
            raise PException('Problem property "{}" missing', property)
        return multilineExpand(name, problem[property])

    def multilineExpand(name, authors):
        result = []
        for author in map(expand, authors.split(" ")):
            result += [aligned(name, author)]
            name = ""
        return result

    def aligned(name, value):
        return text("{:<21} {}", name, value)

    def expand(author):
        if not "juror." + author in contest:
            raise PException('Cannot find juror "{}"', author)
        return contest["juror." + author]

    print(util.join(problemDir, os.path.basename(file)))
    util.writeFile(util.join(problemDir, os.path.basename(file)), "{}", "\n".join([
            line,
            text("{}", contest["name-1"]),
            text("{}", contest["name-2"]),
            text("{}", contest["location"] + ", " + contest["date"]),
            line,
            text("Problem {}. {}",  problem.alias, problem.name),
            text("")
        ]
        + multiline("Original idea", "idea")
        + multiline("Problem statement", "statement")
        + multiline("Test set", "testset")
        + ([
            line,
            text("{}", type),
            text(""),
           ] + multilineExpand("Author", author) + [
        ] if type else []) + [
        line,
        "",
        "",
        ]) + "".join(util.readLines(file)))

def bannerSpecial(problemDir, program, type, property):
    problem = loadProblemProperties()
    if programExists(program):
        program = findSuffix(program)
        if not (property in problem):
            raise PException('Property "{}" (author of "{}") missing in problem.properties', property, program)
        try:
            banner(problemDir, findLanguage(program, "archive")["comments"], program, type, problem[property])
        except PException:
            pass

def problem_archive(options):
    problem = loadProblemProperties()
    contest = loadContestProperties()

    problemDir = util.relswd(options.directory) + "/" + problem.id + "/"
    util.cleanDirs(problemDir)

    if not os.path.exists("problem.xml"):
        raise PException('Must run "xml" first, problem.xml not found', problem.id)

    checker, interact, tests = findCheckerAndTests()

    bannerSpecial(problemDir, "Check", "Checker", "checker")
    bannerSpecial(problemDir, "Interact", "Interactor", "interact")
    bannerSpecial(problemDir, "Tests", "Tests", "testset")
    banner(problemDir, languages_util.comments_xml, "problem.xml")
    banner(problemDir, languages_util.comments("%", "%", "%"), statements(options), "Problem statement", problem["statement"])
    util.copyToDir("problem.properties", problemDir)

    if os.path.exists("tests.sha256"):
        util.copyToDir("tests.sha256", problemDir)

    for language in [l for l in languages.languages if l["comments"]]:
        for file in os.listdir():
            if file.endswith(language["suffix"]) and file.find("_") != -1:
                options.solution = file
                options.test = None
                try:
                    if options.no_check or not problem_check(options):
                        log.info("Copying solution {} to archive", file)
                        banner(problemDir, language["comments"], file, "Solution")
                except PException as e:
                    log.warning(e.message)

    return 0

parser_archive = subparsers.add_parser(
    'archive',
    aliases = 'a',
    help = 'Creates official archive [p]',
    description = """
        Copies correct solutions, checkes, test generators, etc into a
        "__archive" directory. All files are prepended with contest banners.
        You must successfully use "build" and "xml" subcommand before using
        archive subcommand.
    """,
    parents = [parser_check_parent],
    formatter_class = HelpFormatter
)
parser_archive.add_argument('statements', metavar='STATEMENTS', help = 'problem statements directory')
parser_archive.add_argument("-d", "--directory", help = "directory to write result to")
parser_archive.add_argument("-n", "--no-check", action = 'store_true', help = "do not check solutions")
parser_archive.set_defaults(func = recProblem("archive", "Creating archive", problem_archive), directory = "__archive")

def statements(options):
    problem = loadProblemProperties()
    return util.join(options.statements, problem.id + ".tex")

#noinspection PyUnboundLocalVariable
def problem_examples(options):
    problem = loadProblemProperties()
    statementsFile = statements(options)
    if not os.path.exists(statementsFile):
        raise PException('Statements "{}" not found ', problem.id, statementsFile)

    checker, interact, tests = findCheckerAndTests()

    def unescapeTex(line):
        return (
            line
            .replace("\~", "---###TILDE###---")
            .replace("~", " ")
            .replace("$\\sim$", "~")
            .replace("{}", "")
            .replace("\\\\", "---###SLASH###---").replace("\\", "").replace("---###SLASH###---", "\\")
            .replace("---###TILDE###---", "~")
        )

    def diff(expected, found):
        if len(expected) != len(found):
            log.error("Expected {} lines, found {} lines", len(expected), len(found))
        for i in range(0, len(expected)):
            def removeN(s):
                return s[0:len(s) - 1]
            if (expected[i] != found[i]):
                log.error("Line {} differs\nexpected: '{}'\nfound:    '{}'", i + 1, removeN(expected[i]), removeN(found[i]))
                return 1
            pass
        return 0

    interactive = programExists("Interact")
    if interactive:
        make("Interact")

    tests = 0
    state = ["first"]
    input = []
    output = []
    for rline in util.readLines(statementsFile):
        line = rline.strip()
        if (state[0] == "first"):
            if (line.find("\\begin{problem}") != -1):
                def compare(description, expected, actual):
                    if expected != actual:
                        raise PException('{} mismatch.\nExpected "{}"\nFound    "{}"', description, expected, actual)
                parts = line.split("}{")
                if (len(parts) != 5 or parts[4][-1:] != "}"):
                    raise PException("Unsupported problem header format: {}", line)

                name, inf, ouf, tl = parts[1:]
                compare("Problem name", problem.name, name)
                if interactive:
                    compare("Input file name", "standard input", inf)
                    compare("Output file name", "standard output", ouf)
                else:
                    compare("Input file name", problem.input, inf)
                    compare("Output file name", problem.output, ouf)
                if not tl == "\\timeLimit}":
                    compare("Time limit", problem.timeLimit.split("s")[0], tl.split(" second")[0])

                state[0] = "none"
        elif state[0] == "none":
            if line == "\\exmp{":
                tests += 1
                state[0] = "input"
                input[0:len(input)] = []
        elif state[0] == "input":
            if line == "}{":
                state[0] = "output"
                output[0:len(output)] = []
            else:
                input += [unescapeTex(rline)]
        elif state[0] == "output":
            if line == "}" or line == "}%":
                state[0] = "none"
                tf = problem.test(tests)
                inf = tf.input
                ouf = "output.__"
                util.writeFile(ouf, "{}", "".join(output))
                if interactive:
                    shutil.copy(inf, problem.input)
                    with open("output.__") as stdin:
                        with open("input.__", "w") as stdout:
                            run("Interact", stdin=stdin, stdout=stdout)
                    ouf = problem.output
                    inf = problem.input
                    if diff(input, util.readLines("input.__")):
                        raise PException('Example input {} is not equal to test.',
                            problem.id, tests)
                else:
                    if diff(input, util.readLines(inf)):
                        raise PException('Example input {} is not equal to test.',
                            problem.id, tests)

                if run("Check", inf, ouf, tf.answer):
                    raise PException('Example output {} rejected by checker.',
                        problem.id, tests)
                util.removeFiles("__output")
            else:
                output += [unescapeTex(rline)]
    if state[0] != "none":
        raise PException('Invalid examples murkup.')
    if tests == 0:
        raise PException('No examples found.')
    log.info("{} example(s) checked", tests)
    return 0

parser_examples = subparsers.add_parser(
    'examples',
    aliases = 'e',
    help = 'Checks examples from problem statements [p]',
    description = """
        Extracts sample inputs and output from problem statements.
        Compares first tests from test set and extracted sample inputs.
        Run checker to verify the correctness of sample outputs.
        You must successfully use "build" subcommand before using examples subcommand.
    """,
    formatter_class = HelpFormatter
)
parser_examples.add_argument('statements', metavar='STATEMENTS', help = 'problem statements directory')
parser_examples.set_defaults(func = recProblem("examples", "Checking examples", problem_examples))





def contest_clean(options):
    util.removeFiles("challenge.xml")
    return 0

def problem_clean(options):
    problem = loadProblemProperties()

    testsDir = problem.testsDir
    if programExists(util.join(testsDir, "doall")):
        util.removeFiles(*[test.input for test in problem.allTests()])
    if programExists("Tests"):
        util.removeDirs(testsDir)
    for test in problem.allTests():
        if programExists(util.join(testsDir, "do" + test.name)):
            util.removeFiles(test.input)

    util.removeFiles(*[test.answer for test in problem.allTests()])
    util.removeFiles(*[
        util.join(dir, filename)
        for dir in filter(os.path.exists, [".", testsDir])
        for filename in os.listdir(dir)
        for suffix in defaults.cleanSuffixes
        if filename.endswith(suffix)
    ])
    util.removeFiles("run.dat", "problem.xml", "t-run.err")

    return 0

parser_clean = subparsers.add_parser(
    'clean',
    aliases = 'e',
    help = 'Cleans contest and problem directories [cp]',
    description = """
        Cleans all auxiliary files that might have been created during "build",
        "xml", and "check" operations.
    """,
    formatter_class = HelpFormatter
)
parser_clean.set_defaults(func = recContestProblem("clean", "Cleaning directory", contest_clean, problem_clean))



def problem_validate(options):
    problem = loadProblemProperties()
    make("Validate")

    checker, interact, tests = findCheckerAndTests()
    for test in tests:
        with open(test.input) as stdin:
            log.info("Validating test {}", test.name)
            exitcode = run("Validate", stdin=stdin)
            if exitcode:
                raise PException("Validate exit code {} on test {}", exitcode, test.name)
    return 0

parser_validate = subparsers.add_parser(
    'validate',
    aliases = 'v',
    help = 'Validates tests [p]',
    description = """
        Checks that "validator" solution runssuccesfully on each test.
        Validator output is discarded. You must successfully use "build"
        subcommand before using examples subcommand.
    """,
    parents = [parser_time_parent]
)
parser_validate.set_defaults(func = recProblem("validate", "Validate tests", problem_validate))



def input(options):
    problem = loadProblemProperties()
    test = problem.test(options.test)
    if not test.inputExists():
        raise PException('Input file "{}" not found', test.input)
    if not test.answerExists():
        raise PException('Answer file "{}" not found', test.answer)
    shutil.copyfile(test.input, problem.inputFile)
    shutil.copyfile(test.answer, problem.answerFile)
    return 0

parser_input = subparsers.add_parser(
    'input',
    aliases = 'i',
    help = 'Copies test file',
    description = """
        Copies specified test and answer files from testset.
    """,
    formatter_class = HelpFormatter
)
parser_input.add_argument('test', metavar='TEST', help = 'test to copy')
parser_input.set_defaults(func = input)



def idea(options):
    modules = []
    def moduleFile():
        return loadProblemProperties()["id"] + ".iml"

    if not options.clean:
        def createModule(options):
            module = moduleFile()
            util.writeFile(module, "{}", textwrap.dedent(
                """<?xml version="1.0" encoding="UTF-8"?>
                   <module type="JAVA_MODULE" version="4">
                     <component name="NewModuleRootManager" inherit-compiler-output="true">
                       <exclude-output />
                       <content url="file://$MODULE_DIR$">
                         <sourceFolder url="file://$MODULE_DIR$" isTestSource="false" />
                       </content>
                       <orderEntry type="inheritedJdk" />
                       <orderEntry type="sourceFolder" forTests="false" />
                       <orderEntry type="library" name="testlib4j" level="project" />
                       <orderEntry type="module-library">
                         <library>
                           <CLASSES>
                             <root url="file://$MODULE_DIR$/lib" />
                           </CLASSES>
                           <jarDirectory url="file://$MODULE_DIR$/lib" recursive="false"/>
                         </library>
                       </orderEntry>
                     </component>
                   </module>"""))
            modules.append(os.path.relpath(os.path.abspath(module), util.swd))
            return 0

        recProblem("idea", "Generating module", createModule)(options)
        util.mkdirs(".idea", ".idea/libraries")
        util.writeFile(".idea/modules.xml", textwrap.dedent(
             """<?xml version="1.0" encoding="UTF-8"?>
                <project version="4">
                  <component name="ProjectModuleManager">
                    <modules>
                        {modules}
                    </modules>
                  </component>
                </project>"""),
            modules = "\n".join([
                '<module fileurl="file://{file}" filepath="{file}"/>'
                .format(file = "$PROJECT_DIR$/" + module.replace("\\", "/"))
                for module in modules
            ])
        )
        util.writeFile(".idea/workspace.xml", textwrap.dedent(
             """<?xml version="1.0" encoding="UTF-8"?>
                <project version="4">
                  <component name="RunManager" selected="Application.kingdom_gk">
                    <configuration default="true" type="Application" factoryName="Application">
                      <option name="VM_PARAMETERS" value="-Xmx1024m -Xss64m" />
                      <option name="PROGRAM_PARAMETERS" value="-ea" />
                      <option name="WORKING_DIRECTORY" value="file://$MODULE_DIR$" />
                    </configuration>
                  </component>
                </project>
            """))
        util.writeFile(".idea/misc.xml", "{}",
             """<?xml version="1.0" encoding="UTF-8"?>
                <project version="4">
                  <component name="ProjectRootManager" version="2" languageLevel="JDK_1_8" assert-keyword="true" jdk-15="true" project-jdk-name="1.8" project-jdk-type="JavaSDK">
                    <output url="file://$PROJECT_DIR$/.idea/out" />
                  </component>
                </project>
            """)
        testlibDir = "../testlib/"
        util.writeFile(".idea/libraries/testlib4j.xml",
            """<component name="libraryTable">
                 <library name="testlib4j">
                   <CLASSES>
                     {}
                   </CLASSES>
                 </library>
               </component>
            """,
            "\n".join([
                '<root url="jar://$PROJECT_DIR$/{}{}!/"/>'.format(testlibDir, file)
                for file in os.listdir(testlibDir)
                if file.endswith(".jar")
            ])
        )
    else:
        def removeModule(options):
            util.removeFiles(moduleFile())
            return 0
        recProblem("idea", "Removing module", removeModule)(options)
        util.removeDirs(".idea")
    return 0

parser_idea = subparsers.add_parser(
    'idea',
    help = 'Generates IntelliJ IDEA project',
    description = """
        Generates IntelliJ IDEA project for problems found
        in the current directory and subdirectories.

        When runned using "--clean" options removes created
        .iml files and .idea directories.
    """,
    formatter_class = HelpFormatter
)
parser_idea.set_defaults(func = idea)
parser_idea.add_argument("-c", "--clean", action = 'store_true', help = 'clean created files')


def parseArgs(args):
    chunks = []
    for token in args:
        if token == "+":
            chunks = [[]] + chunks
        else:
            chunks[0].append(token)
    chunks.reverse()

    optionss = []
    for chunk in chunks:
        options = parser.parse_args(chunk)
        optionss.append(options)
        if not "func" in options:
            print(header.replace("\\n", "") + '\nUse "p --help" to get help')
            raise PException("Invalid command line")
    return optionss

if __name__ == "__main__":
    try:
        optionss = parseArgs(["+"] + sys.argv[1:])
        if optionss[0].dir != "current directory":
            os.chdir(optionss[0].dir)
        util.swd = os.getcwd()
        for options in optionss:
            util.options = options
            exitcode = options.func(options)
            if exitcode:
                exit(exitcode)
        exit(0)
    except PException as e:
        log.error("{}", e.message)
        util.writeFile("t.out", "{}", e.message)
        exit(1)
    except KeyboardInterrupt:
        log.warning("Interrupted by ^C")
        exit(1)
    except OSError as e:
        log.error("SYSTEM ERROR: {}", str(e))
        exit(1)
