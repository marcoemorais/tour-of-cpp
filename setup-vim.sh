#!/usr/bin/env bash

apt-get install -y fzf vim

NERDTREE_TAG=6.9.11
git clone https://github.com/preservim/nerdtree.git ~/.vim/pack/vendor/start/nerdtree --branch $NERDTREE_TAG

FZF_TAG=0.24.4
git clone https://github.com/junegunn/fzf.git ~/.vim/pack/plugin/start/fzf --branch $FZF_TAG

