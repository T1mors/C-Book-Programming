from locale import D_T_FMT
import subprocess
import seaborn as sns
import pandas as pd


N = 5

df = pd.DataFrame()


for x in range(N):
    for y in range(N):
        with subprocess.Popen(
                ["./test", f"{N}", f"{x}", f"{y}"], stdout=subprocess.PIPE, stdin=subprocess.PIPE, close_fds=True
            ) as p:
            
            output = p.communicate()[0].decode("utf-8")

        num = int(output.split(":")[-1])

        df.loc[y, x] = num

ax = sns.heatmap(df, annot=True, fmt=".4g")
ax.set_xlabel("x")
ax.set_ylabel("y")

ax.get_figure().savefig(f"result_{N}.png")


print("done")