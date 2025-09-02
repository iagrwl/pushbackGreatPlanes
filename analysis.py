import pandas as pd
import matplotlib.pyplot as plt

plt.style.use('dark_background')

csv_file = '/Users/parthamradkar/Downloads/stall_log.csv'
df = pd.read_csv(csv_file)
df['time_s'] = df['time_ms'] / 1000

# choose motor group
print("Choose motor group to display:")
print("1 - Front Intake")
print("2 - Color Sorter")
print("3 - Middle Rollers")
print("4 - Scoring Roller")
print("5 - All Motors")
motor_choice = input("Enter 1-5: ").strip()

# figure setup
fig, axes = plt.subplots(3, 1, figsize=(12, 10), sharex=True)

# helper to select column suffix
motor_map = {
    '1': 'frontIntake',
    '2': 'colorSortRoller',
    '3': 'middleRollers',
    '4': 'scoringRoller'
}

def plot_rpm(ax, motor=None):
    if motor:
        ax.plot(df['time_s'], df[f'{motor}_rpm'], label=f'{motor} RPM', color='cyan')
    else:
        for key, m in motor_map.items():
            ax.plot(df['time_s'], df[f'{m}_rpm'], label=f'{m} RPM')
    ax.set_ylabel('RPM', color='white')
    ax.legend()
    ax.grid(True, color='gray')
    ax.set_title('Motor RPM over Time', color='white')

def plot_current(ax, motor=None):
    if motor:
        ax.plot(df['time_s'], df[f'{motor}_current'], label=f'{motor} Current', color='cyan')
    else:
        for key, m in motor_map.items():
            ax.plot(df['time_s'], df[f'{m}_current'], label=f'{m} Current')
    ax.set_ylabel('Current (mA)', color='white')
    ax.legend()
    ax.grid(True, color='gray')
    ax.set_title('Motor Current over Time', color='white')

def plot_stall(ax, motor=None):
    if motor:
        ax.step(df['time_s'], df[f'{motor}Stall'], where='post', label=f'{motor} Stall', color='cyan')
    else:
        colors = ['cyan', 'magenta', 'yellow', 'lime']
        for i, (key, m) in enumerate(motor_map.items()):
            ax.step(df['time_s'], df[f'{m}Stall'], where='post', label=f'{m} Stall', color=colors[i])
    ax.set_ylabel('Stall State (0 or 1)', color='white')
    ax.set_xlabel('Time (s)', color='white')
    ax.legend()
    ax.grid(True, color='gray')
    ax.set_title('Motor Stall States over Time', color='white')

motor = motor_map.get(motor_choice, None)
plot_rpm(axes[0], motor)
plot_current(axes[1], motor)
plot_stall(axes[2], motor)

plt.tight_layout()
plt.show()