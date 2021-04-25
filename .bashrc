localuser=$USER

alias l='ls -ahl'
alias cm='cd /proj/i4sp1/$localuser/'
alias ct='cd /proj/i4sp1/$localuser/trunk/'
alias cb='cd /proj/i4sp1/$localuser/branches/'
alias nano='nano -l'
alias nb='nano ~/.bashrc'
alias sc='source ~/.bashrc'
alias sv='svn log -l5 -v https://i4sp.cs.fau.de/ss21/sp1/$localuser'
alias memcheck=memtest

# run valgrind with best settings
memtest() {
  valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes "$@"
}

#run gcc with recommended settings
compile() {
  gcc -std=c11 -pedantic -Wall -Werror -D_XOPEN_SOURCE=700 -o "$@";
}

deadline() {
  /proj/i4sp1/bin/get-deadline "$@";
}

submit() {
  /proj/i4sp1/bin/submit "$@";
}

copy() {
   /proj/i4sp1/bin/copy-public-files-for "$@";
}