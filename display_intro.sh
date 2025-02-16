#!/bin/bash

# Color definitions
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[0;33m'
BLUE='\033[0;34m'
MAGENTA='\033[0;35m'
CYAN='\033[0;36m'
RESET='\033[0m'

# Hide cursor
echo -en "\033[?25l"

# Clear screen and move to top
clear

# Function to show the logo
show_logo() {
	echo -e "\n\n"
	echo -e "${RED}██████╗  ██████╗ ██╗     ███████╗██╗  ██╗ █████╗     ${RESET} ${BLUE}███╗   ███╗ █████╗ ██████╗  ██████╗ ███╗   ██╗███╗   ██╗ █████╗  ${RESET}"
	sleep 0.05
	echo -e "${YELLOW}██╔══██╗██╔═══██╗██║     ██╔════╝██║ ██╔╝██╔══██╗    ${RESET} ${GREEN}████╗ ████║██╔══██╗██╔══██╗██╔═══██╗████╗  ██║████╗  ██║██╔══██╗ ${RESET}"
	sleep 0.05
	echo -e "${CYAN}██████╔╝██║   ██║██║     ███████╗█████╔╝ ███████║    ${RESET} ${MAGENTA}██╔████╔██║███████║██║  ██║██║   ██║██╔██╗ ██║██╔██╗ ██║███████║ ${RESET}"
	sleep 0.05
	echo -e "${RED}██╔═══╝ ██║   ██║██║     ╚════██║██╔═██╗ ██╔══██║    ${RESET} ${BLUE}██║╚██╔╝██║██╔══██║██║  ██║██║   ██║██║╚██╗██║██║╚██╗██║██╔══██║ ${RESET}"
	sleep 0.05
	echo -e "${YELLOW}██║     ╚██████╔╝███████╗███████║██║  ██╗██║  ██║    ${RESET} ${GREEN}██║ ╚═╝ ██║██║  ██║██████╔╝╚██████╔╝██║ ╚████║██║ ╚████║██║  ██║ ${RESET}"
	sleep 0.05
	echo -e "${CYAN}╚═╝      ╚═════╝ ╚══════╝╚══════╝╚═╝  ╚═╝╚═╝  ╚═╝    ${RESET} ${MAGENTA}╚═╝     ╚═╝╚═╝  ╚═╝╚═════╝  ╚═════╝ ╚═╝  ╚═══╝╚═╝  ╚═══╝╚═╝  ╚═╝ ${RESET}"
}

# Loading animation
show_loading() {
	for i in {1..10}; do
		dots=$((i % 4))
		echo -en "\r${CYAN}Loading$(printf '.%.0s' $(seq 1 $dots)) ${RESET}"
		sleep 0.1
	done
	echo -e "\n"
}

# Main execution
show_logo
show_loading

# Show cursor again
echo -en "\033[?25h"