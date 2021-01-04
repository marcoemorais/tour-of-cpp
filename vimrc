" -----------------------------------------------------------------------------
" Use utf-8.
" -----------------------------------------------------------------------------
set encoding=utf-8
set fileencoding=utf-8
set termencoding=utf-8

" -----------------------------------------------------------------------------
" Use spaces instead of tabs.
" -----------------------------------------------------------------------------
:set ch=4
:set tabstop=4
:set shiftwidth=4
:set expandtab

" -----------------------------------------------------------------------------
" Indenting.
" -----------------------------------------------------------------------------
:set autoindent
:set smartindent
:set cindent

" -----------------------------------------------------------------------------
" Line numbers.
" -----------------------------------------------------------------------------
:set number

" -----------------------------------------------------------------------------
" Search path used by `gf`.
" -----------------------------------------------------------------------------
:set path=**,/usr/include/**,/usr/local/include/**

" -----------------------------------------------------------------------------
" Navigating window splits.
" -----------------------------------------------------------------------------
nnoremap <C-j> <C-w>j
nnoremap <C-k> <C-w>k
nnoremap <C-h> <C-w>h
nnoremap <C-l> <C-w>l

" -----------------------------------------------------------------------------
" Line length ruler.
" -----------------------------------------------------------------------------
noremap <silent> CC :set colorcolumn=80<CR>
noremap <silent> NCC :set colorcolumn=""<CR>

" -----------------------------------------------------------------------------
" Use ctrl-p to bring up fzf.
" -----------------------------------------------------------------------------
nmap <C-P> :FZF<CR>

" -----------------------------------------------------------------------------
" Set current working directory to same as current open file.
" -----------------------------------------------------------------------------
set autochdir

" -----------------------------------------------------------------------------
" Turn on syntax highlighting.
" -----------------------------------------------------------------------------
syntax on

" -----------------------------------------------------------------------------
" Treat .cc as cpp.
" -----------------------------------------------------------------------------
autocmd BufEnter *.cc :setlocal filetype=cpp

" -----------------------------------------------------------------------------
" Remove trailing whitespace from file on save.
" -----------------------------------------------------------------------------
autocmd BufWritePre * :%s/\s\+$//e

