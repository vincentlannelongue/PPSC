import os
import pandas as pd
import matplotlib.pyplot as plt
import seaborn as sns

sns.set_style("whitegrid")

RESULTS_PATH = "results"


def method_0():
    columns = ["k", "pi_approx", "error"]
    zeta0_path = "zeta0/vtest_results.txt"
    mach0_path = "mach0/vtest_results.txt"

    zeta0 = pd.read_csv(zeta0_path, names=columns, sep=" ")
    mach0 = pd.read_csv(mach0_path, names=columns, sep=" ")

    plt.plot(zeta0["k"], zeta0["error"], label="Zeta")
    plt.plot(mach0["k"], mach0["error"], label="Machin")

    plt.xlabel("k", fontsize=14, family="serif")
    plt.ylabel("Error", fontsize=14, family="serif")
    plt.xticks(
        zeta0["k"],
    )
    plt.yscale("log")
    plt.legend(loc="upper right")
    plt.savefig(os.path.join(RESULTS_PATH, "method_0.svg"))
    plt.close()


def method_error(method, num=1):
    path = f"{method}{num}/results.txt"

    columns = ["procs", "n", "pi_approx", "error", "time"]
    df = pd.read_csv(path, names=columns, sep=" ")

    for procs_value, group in df.groupby("procs"):
        plt.plot(group["n"], group["error"], label=f"{procs_value}")
        plt.scatter(group["n"], group["error"])
    plt.xticks(group["n"])
    plt.xlabel("n", fontsize=14, family="serif")
    plt.ylabel("Error", fontsize=14, family="serif")
    plt.yscale("log")
    plt.xscale("log")

    plt.title(f"{method} - Error")
    plt.legend(loc="upper right")
    plt.savefig(os.path.join(RESULTS_PATH, f"{method}_{num}_error.svg"))
    plt.close()


def method_time(method, num=1):
    path = f"{method}{num}/results.txt"

    columns = ["procs", "n", "pi_approx", "error", "time"]
    df = pd.read_csv(path, names=columns, sep=" ")

    for procs_value, group in df.groupby("n"):
        plt.plot(group["procs"], group["time"], label=f"{procs_value}")
        plt.scatter(group["procs"], group["time"])
    plt.xticks(group["procs"])
    plt.xlabel("procs", fontsize=14, family="serif")
    plt.ylabel("Time (s)", fontsize=14, family="serif")
    plt.yscale("log")
    plt.xscale("log")
    plt.title(f"{method} - Time")

    plt.legend(loc="upper right")
    plt.savefig(os.path.join(RESULTS_PATH, f"{method}_{num}_time.svg"))
    plt.close()


def reduc():
    for method, linestyle in zip(
        ["reduc", "doubling"], ["-", "-."]
    ):

        path = f"reduc/results_{method}.txt"
        columns = ["procs", "n", "pi_approx", "error", "time"]
        df = pd.read_csv(path, names=columns, sep=" ")

        for colour, (procs_value, group) in zip(["red", "blue", "green", "brown"], df.groupby("n")):
            plt.plot(
                group["procs"],
                group["time"],
                label=f"{method}-{procs_value}",
                linestyle=linestyle,
                color=colour,
            )
            # plt.scatter(group["procs"], group["time"], color=colour)
    plt.xticks(group["procs"])
    plt.xlabel("procs", fontsize=14, family="serif")
    plt.ylabel("Time (s)", fontsize=14, family="serif")
    plt.yscale("log")
    plt.xscale("log")
    plt.title("Reduction method comparison")

    plt.legend(loc="upper right")
    plt.savefig(os.path.join(RESULTS_PATH, f"reduc_time.svg"))
    plt.close()


if __name__ == "__main__":
    os.makedirs(RESULTS_PATH, exist_ok=True)
    method_0()
    method_error("zeta")
    method_error("mach")
    method_time("zeta")
    method_time("mach")
    reduc()
    method_error("zeta", num=2)
    method_error("mach", num=2)
    method_time("zeta", num=2)
    method_time("mach", num=2)
