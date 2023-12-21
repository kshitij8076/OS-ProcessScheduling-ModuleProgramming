import matplotlib.pyplot as plt
import numpy as np

def get_time():
 
    file = open("../src/output.csv", "r")
    inputs = file.readlines()
    file.close()
    
    process_a = float(inputs[0].split(" ")[6].strip())
    process_b = float(inputs[1].split(" ")[6].strip())
    process_c = float(inputs[2].split(" ")[6].strip())

    return process_a, process_b, process_c

if __name__ == "__main__":
 
    execution_times = get_time()
    processes = ["FIFO", "RR", "OTHER"]
    times = execution_times

    plt.bar(processes, times, color=['red', 'green', 'blue'])
    plt.xlabel("Process")
    plt.ylabel("Execution Time")
    plt.title("Execution Times of Different Processes")
    plt.show()
