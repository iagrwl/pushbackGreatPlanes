import pandas as pd
import numpy as np
import os

# load your base csv
df = pd.read_csv("/Users/parthamradkar/Downloads/stall_log.csv")
df['time_s'] = df['time_ms'] / 1000

# identify motors (columns ending in _rpm)
motors = [col.replace('_rpm', '') for col in df.columns if col.endswith('_rpm')]

# output folder
output_dir = "simulated_csvs"
os.makedirs(output_dir, exist_ok=True)

def simulate_variation(df):
    """make a more randomized variation with jumps and staggered stall states"""
    sim_df = df.copy()
    
    for motor in motors:
        rpm_col = f"{motor}_rpm"
        scale_factor = np.random.uniform(0.9, 1.1)
        
        if rpm_col in sim_df:
            sim_df[rpm_col] *= scale_factor
            
            # introduce multiple random jumps
            num_jumps = np.random.randint(5, 15)
            jump_indices = np.random.choice(len(sim_df), size=num_jumps, replace=False)
            for idx in jump_indices:
                sim_df.loc[idx, rpm_col] *= np.random.uniform(0.2, 0.8)
            
            # add small random noise
            sim_df[rpm_col] += np.random.normal(0, 5, size=len(sim_df))
        
        # current and amp variation
        for suffix in ["current", "amp"]:
            col = f"{motor}_{suffix}"
            if col in sim_df:
                sim_df[col] *= (scale_factor + np.random.uniform(-0.05, 0.05))
                sim_df[col] += np.random.normal(0, 0.1, size=len(sim_df))
        
        # stall variation
        stall_col = f"{motor}Stall"
        if stall_col in sim_df:
            stalls = np.zeros(len(sim_df))
            num_stall_sequences = np.random.randint(2, 5)
            for _ in range(num_stall_sequences):
                start = np.random.randint(0, len(sim_df)-10)
                length = np.random.randint(1, 10)
                stalls[start:start+length] = 1
            sim_df[stall_col] = stalls

    return sim_df

# generate 15 versions
for i in range(1, 17):
    sim_df = simulate_variation(df)
    sim_df.to_csv(f"{output_dir}/variation_{i}.csv", index=False)

print(f"✅ generated 15 variations in folder: {output_dir}")