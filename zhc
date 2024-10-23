autocmd TextChanged,TextChangedI <buffer> silent write
set tabstop=4
set shiftwidth=4
set smarttab
set et " отключает табуляцию и использует пробелы вместо табуляций
set number relativenumber
set exrc
set secure
set colorcolumn=110
highlight ColorColumn ctermbg=darkgray

augroup project
    autocmd!
    autocmd BufRead,BufNewFile *.h,*.c set filetype=c.doxygen
augroup END

let &path.="src/include,/usr/include/AL,"
syntax enable
colorscheme sublimemonokai
set ruler
set laststatus=2
set statusline=%F\ %l:%c
set cursorcolumn
set cursorline
set autoindent
filetype plugin indent on
set incsearch
set ignorecase
set smartcase

