#!/bin/bash

Op=$1
Arg=$2
# Up - git commit -a -m $Arg & git push
# Down - git pull & git checkout main
# Log - git log --oneline
# Cred - git config --global --unset credential.helper & git config --global credential.helper store

#echo Op: !Op!
#echo Arg: !Arg!

case $Op in
	Up)
		if [[ -z $Arg ]]; then
			echo "Usage: GitScript Up <Commit Messages>"
			exit
		fi
		echo "Will execute: git commit -a -m $Arg, git push"
		read -p "Please confirm [Y/n]: " -n 1 -r
		
		if [[ $REPLY =~ ^[Nn]$ ]]; then
			exit
		fi
		
		echo "Commiting..."
		git add --all
		git commit -a -m $Arg
		echo "Pushing..."
		git push
		;;
	Down)
		echo "Will execute: git pull, git checkout main"
		read -p "Please confirm [Y/n]: " -n 1 -r
		
		if [[ $REPLY =~ ^[Nn]$ ]]; then
			exit
		fi
		
		echo "Pulling..."
		git pull
		echo "Checking out..."
		git checkout main
		;;
	Log)
		git log --oneline
		;;
	Cred)
		echo "Will execute: git config --global --unset credential.helper, git --global config credential.helper store"
		read -p "Please confirm [Y/n]: " -n 1 -r
		
		if [[ $REPLY =~ ^[Nn]$ ]]; then
			exit
		fi
		
		git config --global --unset credential.helper
		git config --global credential.helper store
		;;
	*)
		echo "Usage: GitScript ^<Option^> [Optional Argument]"
		echo "Available options:"
		echo "	Up	Commit and push to remote, require optional argument: commit message"
		echo "	Down	Pull and checkout main branch"
		echo "	Log	Check git one-line log"
		echo "	Cred	Remove and update credential in next operation"
		exit
		;;
esac

echo "Command completed."
