import util

timelimit = "2s"
memorylimit = "536870912"

testsDir = "tests"
contestProperties = {
    "name-1": "",
    "name-2": "",
    "location": "",
    "date": "",
    "timelimit": timelimit,
    "memorylimit": memorylimit,
    "problem-prefix": "",
    "testsdir": testsDir,
}

exe = ".exe" if util.windows else ".exe"

stopOnFirstError = False
cleanSuffixes = [exe, ".dcu", ".obj", ".class", ".jar", ".hi", ".o", ".manifest", ".log", ".in", ".out", ".ans", ".__"]
runOptions = [
    "-Xacp", "-x", "-y", "10s", "-r", "0.05",
    "-s", "run.dat", "-o", "t-run.out", "-e", "t-run.err"
]
javaOptions = ["-Xmx512m", "-Xss64m", "-ea"]
javacOptions = ["-encoding", "utf8"]
javaClasspath = [util.relpath("testlib/*"), "lib/*"]
allow64bits = True
removeInputAndOutput = False
