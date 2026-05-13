import pandas as pd
import matplotlib.pyplot as plt
import glob
import os

# Set style for professional-looking plots
plt.style.use('seaborn-v0_8-whitegrid')

def create_performance_plots():
    # File mapping: looking one directory up ('../') from the Plots folder
    files = {
        'Original': '../results_og.csv',
        'Parallel Naive': '../results_arch2.csv',
        'Loop Interchange': '../results_arch3.csv',
        'Optimised': '../results_optimised.csv'
    }
    
    data = {}
    for name, file in files.items():
        if os.path.exists(file):
            # Reading CSV rows (expects 20 rows for 20 threads)
            df = pd.read_csv(file, names=['Threads', 'Time'])
            data[name] = df
    
    if not data:
        print("Error: results_*.csv files not found in the parent directory!")
        return

    # --- Plot 1: Execution Time ---
    plt.figure(figsize=(10, 6))
    for name, df in data.items():
        plt.plot(df['Threads'], df['Time'], marker='o', label=name)
    plt.yscale('log')
    plt.xlabel('Threads')
    plt.ylabel('Time (ms) - Log Scale')
    plt.title('1. Execution Time per Version')
    plt.legend()
    plt.savefig('plot_1_execution_time.png')
    print("Generated: plot_1_execution_time.png")

    # --- Plot 2: Speedup ---
    plt.figure(figsize=(10, 6))
    # Reference ideal line
    threads_ref = data['Optimised']['Threads']
    plt.plot(threads_ref, threads_ref, '--', color='gray', label='Ideal Speedup')
    
    for name, df in data.items():
        if name == 'Original': continue
        t1 = df[df['Threads'] == 1]['Time'].values[0]
        speedup = t1 / df['Time']
        plt.plot(df['Threads'], speedup, marker='s', label=f'{name} Speedup')
    
    plt.xlabel('Threads')
    plt.ylabel('Speedup (x)')
    plt.title('2. Speedup Analysis')
    plt.legend()
    plt.savefig('plot_2_speedup.png')
    print("Generated: plot_2_speedup.png")

    # --- Plot 3: Efficiency ---
    plt.figure(figsize=(10, 6))
    plt.axhline(y=1, color='gray', linestyle='--', label='Ideal Efficiency (1.0)')
    
    for name, df in data.items():
        if name == 'Original': continue
        t1 = df[df['Threads'] == 1]['Time'].values[0]
        speedup = t1 / df['Time']
        efficiency = speedup / df['Threads']
        plt.plot(df['Threads'], efficiency, marker='d', label=f'{name} Efficiency')
    
    plt.ylim(0, 1.1)
    plt.xlabel('Threads')
    plt.ylabel('Efficiency')
    plt.title('3. Resource Efficiency')
    plt.legend()
    plt.savefig('plot_3_efficiency.png')
    print("Generated: plot_3_efficiency.png")

def create_scalability_plots():
    list_of_files = glob.glob('../matrix_size_output_*.csv')
    if not list_of_files:
        print("Error: Scalability CSV (matrix_size_output_*) not found.")
        return
    
    latest_file = max(list_of_files, key=os.path.getctime)
    df = pd.read_csv(latest_file, names=['Threads', 'Small (512)', 'Medium (1024)', 'Large (2048)'])

    # --- Plot 4: Scalability Execution Time ---
    plt.figure(figsize=(10, 6))
    for col in ['Small (512)', 'Medium (1024)', 'Large (2048)']:
        plt.plot(df['Threads'], df[col], marker='v', label=col)
    plt.yscale('log')
    plt.xlabel('Threads')
    plt.ylabel('Time (ms)')
    plt.title('4. Scalability: Execution Time')
    plt.legend()
    plt.savefig('plot_4_scalability_time.png')
    print("Generated: plot_4_scalability_time.png")

    # --- Plot 5: Scalability Speedup ---
    plt.figure(figsize=(10, 6))
    plt.plot(df['Threads'], df['Threads'], '--', color='gray', label='Ideal')
    for col in ['Small (512)', 'Medium (1024)', 'Large (2048)']:
        t1 = df[col].iloc[0]
        speedup = t1 / df[col]
        plt.plot(df['Threads'], speedup, marker='^', label=f'Speedup {col}')
    plt.xlabel('Threads')
    plt.ylabel('Speedup')
    plt.title('5. Scalability: Speedup')
    plt.legend()
    plt.savefig('plot_5_scalability_speedup.png')
    print("Generated: plot_5_scalability_speedup.png")

if __name__ == "__main__":
    create_performance_plots()
    create_scalability_plots()
    print("\nAll 5 plots successfully generated in the Plots folder!")