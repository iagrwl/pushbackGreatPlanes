import pandas as pd
import matplotlib.pyplot as plt
import os

# dark background style
plt.style.use('dark_background')

# input and output folders
input_dir = "/Users/parthamradkar/Downloads/simulated_csvs"
output_dir = "/Users/parthamradkar/Downloads/simulated_graphs"
os.makedirs(output_dir, exist_ok=True)

# all csv files in the input folder
csv_files = [f for f in os.listdir(input_dir) if f.endswith(".csv")]

for file in csv_files:
    df = pd.read_csv(os.path.join(input_dir, file))
    if 'time_ms' in df.columns:
        df['time_s'] = df['time_ms'] / 1000

    motors = [col.replace('_rpm', '') for col in df.columns if col.endswith('_rpm')]

    fig, axes = plt.subplots(3, 1, figsize=(12, 12), sharex=True)

    # RPM plot
    for motor in motors:
        rpm_col = f"{motor}_rpm"
        if rpm_col in df:
            axes[0].plot(df['time_s'], df[rpm_col], label=f"{motor} RPM")
    axes[0].set_title(f"{file} - Motor RPM")
    axes[0].legend()

    # Current plot
    for motor in motors:
        for suffix in ["current", "amp"]:
            col = f"{motor}_{suffix}"
            if col in df:
                axes[1].plot(df['time_s'], df[col], label=f"{motor} {suffix}")
    axes[1].set_title(f"{file} - Motor Current")
    axes[1].legend()

    # Stall plot
    for motor in motors:
        stall_col = f"{motor}Stall"
        if stall_col in df:
            axes[2].step(df['time_s'], df[stall_col], label=f"{motor} Stall", where="post")
    axes[2].set_title(f"{file} - Stall State")
    axes[2].legend()

    plt.tight_layout()
    out_path = os.path.join(output_dir, file.replace(".csv", ".png"))
    plt.savefig(out_path)
    plt.close()

print(f"✅ graphs saved to: {output_dir}")