let g:clang_library_path='/usr/lib/llvm-17/lib/libclang-17.so.1'
let g:hardhacker_darker = 1
let g:lsc_server_commands = {'c++' : 'clangd'}
let g:indentLine_color_term = 240
let g:indentLine_char = '┆'
let g:lsp_inlay_hints_enabled = 1

syntax      enable
syntax      on
set         t_Co=256
set encoding=utf-8
set number

autocmd VimEnter * NERDTree

nnoremap <leader>n :NERDTreeFocus<CR>
nnoremap <C-n> :NERDTree<CR>
nnoremap <C-t> :NERDTreeToggle<CR>
nnoremap <C-f> :NERDTreeFind<CR>
nnoremap <C-s> :w<CR>

"au TextChanged, TextChangedP * call :LspDocumentDiagnostics

let data_dir = has('nvim') ? stdpath('data') . '/site' : '~/.vim'
if empty(glob(data_dir . '/autoload/plug.vim'))
  silent execute '!curl -fLo '.data_dir.'/autoload/plug.vim --create-dirs  https://raw.githubusercontent.com/junegunn/vim-plug/master/plug.vim'
  autocmd VimEnter * PlugInstall --sync | source $MYVIMRC
endif

call plug#begin()

  Plug 'prabirshrestha/vim-lsp'
  Plug 'mattn/vim-lsp-settings'
  Plug 'prabirshrestha/asyncomplete.vim'
  Plug 'prabirshrestha/asyncomplete-lsp.vim'
  Plug 'itchyny/lightline.vim'
  Plug 'maximbaz/lightline-ale'
 "Plug 'jiangmiao/auto-pairs'
  Plug 'yggdroot/indentline'
  Plug 'hardhackerlabs/theme-vim', { 'as': 'hardhacker' }
	Plug 'vim-airline/vim-airline'
  Plug 'sheerun/vim-polyglot'

call plug#end()

if executable('clangd')
    augroup lsp_clangd
        autocmd!
autocmd User lsp_setup call lsp#register_server({
                    \ 'name': 'clangd',
                    \ 'cmd': {server_info->['clangd --all-scopes-completeion']},
                    \ 'whitelist': ['c', 'cpp', 'objc', 'objcpp'],
                    \ })
        autocmd FileType c setlocal omnifunc=lsp#complete
        autocmd FileType cpp setlocal omnifunc=lsp#complete
        autocmd FileType objc setlocal omnifunc=lsp#complete
        autocmd FileType objcpp setlocal omnifunc=lsp#complete
    augroup end
endif

colorscheme hardhacker
