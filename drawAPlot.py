import matplotlib.pyplot as plt

def create_plot_from_file(file_path):
    with open(file_path, 'r') as file:
        numbers = [float(line.strip()) for line in file]

    plt.plot(numbers)
    plt.xlabel('Game index')
    plt.ylabel('Credits')
    plt.title('Change of credits amount.')
    plt.grid(True)
    plt.savefig('wallet_content_plot.png')
    plt.show()

if __name__ == "__main__":
    import sys
    if len(sys.argv) != 2:
        print("Usage: python drawAPlot.py <file_path>")
        sys.exit(1)
    
    file_path = sys.argv[1]
    create_plot_from_file(file_path)

