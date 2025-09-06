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
print("5 - Left DT m7")
print("6 - Left DT m6")
print("7 - Left DT m5")
print("8 - Right DT m14")
print("9 - Right DT m15")
print("10 - Right DT m16")
print("11 - All Motors")
print("12 - All Drivetrain Motors")
motor_choice = input("Enter 1-12: ").strip()

# figure setup
fig, axes = plt.subplots(2, 1, figsize=(12, 8), sharex=True)

# helper to select column suffix
motor_map = {
    '1': ('frontIntake', True),
    '2': ('colorSortRoller', True),
    '3': ('middleRollers', True),
    '4': ('scoringRoller', True),
    '5': ('leftDT_m7', False),
    '6': ('leftDT_m6', False),
    '7': ('leftDT_m5', False),
    '8': ('rightDT_m14', False),
    '9': ('rightDT_m15', False),
    '10': ('rightDT_m16', False)
}

dt_motors = ['leftDT_m7', 'leftDT_m6', 'leftDT_m5',
             'rightDT_m14', 'rightDT_m15', 'rightDT_m16']

def plot_rpm(ax, motor=None, intake=True, group=None):
    if motor:
        ax.plot(df['time_s'], df[f'{motor}_rpm'], label=f'{motor} RPM', color='cyan')
    elif group == "dt":
        for m in dt_motors:
            ax.plot(df['time_s'], df[f'{m}_rpm'], label=f'{m} RPM')
    else:
        for key, (m, _) in motor_map.items():
            ax.plot(df['time_s'], df[f'{m}_rpm'], label=f'{m} RPM')
    ax.set_ylabel('RPM', color='white')
    ax.legend()
    ax.grid(True, color='gray')
    ax.set_title('Motor RPM over Time', color='white')

def plot_current(ax, motor=None, intake=True, group=None):
    if motor:
        suffix = 'current' if intake else 'amp'
        ax.plot(df['time_s'], df[f'{motor}_{suffix}'], label=f'{motor} Current', color='cyan')
    elif group == "dt":
        for m in dt_motors:
            suffix = 'amp'
            ax.plot(df['time_s'], df[f'{m}_{suffix}'], label=f'{m} Current')
    else:
        for key, (m, intake) in motor_map.items():
            suffix = 'current' if intake else 'amp'
            ax.plot(df['time_s'], df[f'{m}_{suffix}'], label=f'{m} Current')
    ax.set_ylabel('Current (mA)', color='white')
    ax.legend()
    ax.grid(True, color='gray')
    ax.set_title('Motor Current over Time', color='white')

if motor_choice in motor_map:
    motor, intake = motor_map[motor_choice]
    plot_rpm(axes[0], motor, intake)
    plot_current(axes[1], motor, intake)
elif motor_choice == '12':
    plot_rpm(axes[0], group="dt")
    plot_current(axes[1], group="dt")
else:
    plot_rpm(axes[0], None)
    plot_current(axes[1], None)

plt.tight_layout()
plt.show()