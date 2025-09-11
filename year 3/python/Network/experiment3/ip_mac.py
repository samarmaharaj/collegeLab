import subprocess
import re
import platform

def get_network_info():
    """
    Runs system commands to get network interface info and parses the output.
    """
    system = platform.system()
    
    # Use 'ipconfig /all' on Windows
    if system == "Windows":
        command = "ipconfig /all"
        # Use a specific encoding that works for Windows command output
        encoding = 'oem' 
    # Use 'ifconfig -a' on Linux and macOS
    else:
        command = "ifconfig -a"
        encoding = 'utf-8'

    try:
        # Run the command and capture the output
        output = subprocess.check_output(command, shell=True, text=True, encoding=encoding)
    except (subprocess.CalledProcessError, FileNotFoundError) as e:
        print(f"Error executing command: {e}")
        print("Please ensure 'ifconfig' (Linux/macOS) or 'ipconfig' (Windows) is installed and in your PATH.")
        return

    # Regular expressions to find addresses
    # This regex looks for MAC addresses in various common formats
    mac_regex = r"([0-9a-fA-F]{2}[-:]){5}([0-9a-fA-F]{2})"
    # This regex finds IPv4 addresses
    ipv4_regex = r"\b\d{1,3}\.\d{1,3}\.\d{1,3}\.\d{1,3}\b"
    # This regex is a simplified version for finding IPv6 addresses
    ipv6_regex = r"([0-9a-fA-F]{1,4}:){7,7}[0-9a-fA-F]{1,4}|([0-9a-fA-F]{1,4}:){1,7}:|:((:[0-9a-fA-F]{1,4}){1,7}|:)"


    print(f"Network information for {system}:\n")
    
    # The output of ipconfig/ifconfig groups info by interface
    # So we split the output by common delimiters to process each interface block
    if system == "Windows":
        # In Windows, "Wireless LAN adapter" or "Ethernet adapter" starts a new block
        interface_blocks = re.split(r'\n(?=[A-Za-z])', output)
    else:
        # On Linux/macOS, interfaces are often separated by a blank line or start with a name at the beginning of a line
        interface_blocks = re.split(r'\n(?=[^\s])', output)

    for block in interface_blocks:
        if not block.strip():
            continue

        mac_addresses = re.findall(mac_regex, block)
        ipv4_addresses = re.findall(ipv4_regex, block)
        ipv6_addresses = re.findall(ipv6_regex, block)
        
        # Filter out invalid IPs like 0.0.0.0
        ipv4_addresses = [ip for ip in ipv4_addresses if ip != '0.0.0.0' and not ip.startswith('255.')]

        # We only print the block if it contains a valid MAC or IP address
        if mac_addresses or ipv4_addresses or ipv6_addresses:
            print("----------------------------------------")
            print(block.splitlines()[0]) # Print the first line as the interface name/description
            
            if mac_addresses:
                # The regex returns tuples, so we join them to form the full address string
                full_mac = "".join(mac_addresses[0])
                print(f"  MAC Address:    {full_mac}")
            
            if ipv4_addresses:
                print(f"  IPv4 Address:   {ipv4_addresses[0]}")
            
            if ipv6_addresses:
                # We may find multiple IPv6 addresses (e.g., link-local), just show the first one
                print(f"  IPv6 Address:   {ipv6_addresses[0]}")


if __name__ == "__main__":
    get_network_info()