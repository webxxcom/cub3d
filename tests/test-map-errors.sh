#!/bin/bash
execPath="cub3D"
makePath="."
mapsPath='tests/maps/'

termwidth="$(tput cols)"
green='\e[1;32m'
yellow='\e[93m'
blueBg='\e[46m'
blue='\e[34m'
red='\e[31m'
end='\e[0m'
passed=0
failed=0

launch_valgrind () {
	vg_output="$(
		timeout "2s" \
		valgrind --leak-check=full \
		         --show-leak-kinds=all \
		         --track-origins=yes \
		         --errors-for-leak-kinds=all \
				 --suppressions=mlx.supp \
		         --error-exitcode=42 \
		         ./${execPath} ${mapsPath}$1 2>&1
	)"
	vg_exit=$?

	printf "${red}Valgrind output:${end}\n"
	printf "%s\n" "$vg_output"

	return $vg_exit
}


head () {
  padding="$(printf '=%.0s' {1..500})"
  printf "\n${yellow}%*.*s %s %*.*s${end}\n" 0 "$(((termwidth-5-${#1})/2))" "$padding" "  $1  " 0 "$(((termwidth-6-${#1})/2))" "$padding"
}

log () {
  padding="$(printf '=%.0s' {1..500})"
  printf "${blue}%*.*s %s %*.*s${end}\n" 0 "$(((termwidth-5-${#1})/2))" "$padding" "  $1  " 0 "$(((termwidth-6-${#1})/2))" "$padding"
}

pass () {
  ((passed++))
  padding="$(printf '=%.0s' {1..500})"
  printf "${green}%*.*s %s %*.*s${end}\n\n" 0 "$(((termwidth-5-8)/2))" "$padding" " Passed " 0 "$(((termwidth-6-${#1})/2))" "$padding"
}

fail () {
  ((failed++))
  padding="$(printf '=%.0s' {1..500})"
  printf "${red}%*.*s %s %*.*s${end}\n\n" 0 "$(((termwidth-5-8)/2))" "$padding" " Failed " 0 "$(((termwidth-6-${#1})/2))" "$padding"
}

launch () {
	log "$1"

	if ./${execPath} ${mapsPath}$1; then
		fail
	else
		pass
	fi

	launch_valgrind "$1"
	vg_exit=$?

	if (( vg_exit == 42 )); then
		printf "${red}Stopping tests due to Valgrind failure.${end}\n"
		exit 1
	fi
}


result () {
	if (( failed == 0 )); then
		printf "${green}YEAH ! All tests successfully passed ! Good job !${end}\n"
	else
		printf "${green}${passed}${end} tests passed, ${red}${failed}${end} tests failed.\n"
		printf "Don't worry, im sure you can fix it ! Keep it up !\n"
	fi
}

cd ..

head "Testing Decors"
launch "map-decor-0.cub"
launch "map-decor-1.cub"
launch "map-decor-2.cub"
launch "map-decor-4.cub"
launch "map-decor-5.cub"
launch "map-decor-6.cub"
launch "map-decor-7.cub"

head "Testing NO texture"
launch "map-no-0.cub"
launch "map-no-1.cub"
launch "map-no-2.cub"
launch "map-no-3.cub"
launch "map-no-4.cub"
launch "map-no-5.cub"
launch "map-no-6.cub"
launch "map-no-7.cub"

head "Testing RGB"
launch "map-rgb-0.cub"
launch "map-rgb-1.cub"
launch "map-rgb-2.cub"
launch "map-rgb-3.cub"
launch "map-rgb-4.cub"
launch "map-rgb-5.cub"

head "Testing spawns"
launch "map-spawn-0.cub"
launch "map-spawn-1.cub"
launch "map-spawn-2.cub"

head "DONE"
result