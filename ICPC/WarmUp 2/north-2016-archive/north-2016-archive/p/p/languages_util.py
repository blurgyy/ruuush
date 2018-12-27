import util
import os

import defaults
import log

def runCompiled(program, args):
    return ["./" + util.replaceSuffix(program, defaults.exe)] + args

def noCompile(program):
    return 0

def joinClasspath(classpath):
    return ["-cp", (";" if util.windows else ":").join(classpath)] if classpath else []

def runJar(jar, args = []):
    return java(args = ["-jar", jar] + args)

def java(classpath = [], args = []):
    return [javaHome() + "java"] + defaults.javaOptions + joinClasspath(classpath) + list(args)

myJavaHome = None
def javaHome():
    global myJavaHome
    if myJavaHome is None:
        myJavaHome = ""
        if os.name == "nt":
            if "JAVA_HOME" in os.environ:
                myJavaHome = os.environ["JAVA_HOME"] + "\\bin\\"
            else:
                log.warning("Warining: JAVA_HOME environment variable not set")
    return myJavaHome

def javaToJar(program):
    name = util.deleteSuffix(program)
    temp = "__" + name
    util.removeDirs(temp)
    try:
        util.removeFiles(name + ".jar")
        util.mkdirs(temp, temp + "/META-INF")
        manifest = ["Main-Class: " + name]
        if name == "Check":
            os.chdir(temp)
            util.execute(javaHome() + "jar", "xf", util.relpath("testlib/testlib4j.jar"))
            os.chdir("..")
            manifest = [
                "Main-Class: ru.ifmo.testlib.CheckerFramework",
                "Checker-Class: Check"
            ]
        if name == "Validate" and os.path.exists(util.relpath("testlib/validate4j.jar")):
            os.chdir(temp)
            util.execute(javaHome() + "jar", "xf", util.relpath("testlib/validate4j.jar"))
            os.chdir("..")
            manifest = [
                "Main-Class: ru.ifmo.validate.ValidatorFramework",
                "Checker-Class: Validate"
            ]

        if os.path.isdir("lib/") and os.listdir("lib/") != []:
            manifest += ["Class-Path: " + " ".join(["lib/" + dir for dir in os.listdir("lib/")])]
        manifestFile = temp + "/META-INF/MANIFEST.MF"
        util.writeFile(manifestFile, "{}\n", "\n".join(manifest))

        return util.execute(*[
                javaHome() + "javac",
                "-sourcepath", ".",
                "-d", temp,
            ] + defaults.javacOptions + [
            ] + joinClasspath(defaults.javaClasspath) + [
                program
            ]
        ) or util.execute(
            javaHome() + "jar",
            "cfm", name + ".jar", manifestFile,
            "-C", temp,
            "."
        )
    finally:
        util.removeDirs(temp)

def addArgs(f):
    return (lambda program, args: f(program) + args)

def substituteProgram(program, command):
    return [
        c.format(program = program, programNoSuffix = util.deleteSuffix(program))
        for c in command
    ]

def compiled(suffix, description, comments, compileCommand, run = runCompiled, tempSuffixes = []):
    def compile(program):
        try:
            return util.execute(*substituteProgram(program, compileCommand))
        finally:
            util.removeFiles(*[util.replaceSuffix(program, suffix) for suffix in tempSuffixes])

    return language(suffix, description, comments, compile, run)

def compiledWinLin(suffix, description, comments, compileCommandWin, compileCommandLin, run = runCompiled, tempSuffixes = []):
    return compiled(
        suffix,
        description,
        comments,
        compileCommandWin if util.windows else compileCommandLin,
        run,
        tempSuffixes
    )

def script(suffix, description, comments, runCommand):
    return language(suffix, description, comments, noCompile,
        addArgs(lambda program: substituteProgram(program, runCommand)))

def language(suffix, description, comments, compile, runCommand):
    return dict(
        suffix = suffix,
        description = description,
        comments = comments,
        compile = compile,
        run = runCommand
    )

def comments(begin, line, end):
    return dict(begin = begin, line = line, end = end)

comments_c = comments("/*", "*", "*/")
comments_pascal = comments("(*", "*", "*)")
comments_haskell = comments("{-", "-", "-}")
comments_xml = comments("<!--", "=", "-->")
comments_basic = comments("'", "=", "'")
comments_python = comments("#", "#", "#")
