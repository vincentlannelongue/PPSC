


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

    zeta0 = pd.read_csv(zeta0_path, names=columns, sep=' ')
    mach0 = pd.read_csv(mach0_path, names=columns, sep=' ')

    plt.plot(zeta0["k"], zeta0["error"], label="Zeta")
    plt.plot(mach0["k"], mach0["error"], label="Machin")

    plt.xlabel("k", fontsize=14, family='serif')
    plt.ylabel("Error", fontsize=14, family='serif')
    plt.xticks(zeta0["k"], )
    plt.yscale("log")
    plt.legend(loc='upper right')
    plt.savefig(os.path.join(RESULTS_PATH, "method_0.svg"))
    plt.close()


if __name__ == '__main__':
    os.makedirs(RESULTS_PATH, exist_ok=True)
    method_0()
    
