import pandas as pd
import matplotlib.pyplot as plt
import sys

def main(*args, **kwargs): 
    df = pd.read_csv("result.csv",sep=";")
    writeToFile = False
    if len(sys.argv) > 1:
        writeToFileArg = sys.argv[1]
        writeToFile = writeToFileArg.lower() in ['true', '1', 't', 'y', 'yes']
    plt.plot(df.get('x'), df.get('u(x)'))
    plt.title("Przybliżenie rozwiązania równania odkształcenia elstycznego")
    plt.xlabel("x")
    plt.ylabel("Przybliżone u(x)")
    if not writeToFile:
        plt.show()
    else:
        plt.savefig("plotted.png")
if __name__ == "__main__":
    main()