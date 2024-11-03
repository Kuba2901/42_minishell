{ pkgs ? import <nixpkgs> {} }:
pkgs.mkShell {
  buildInputs = with pkgs; [ 
    gnumake
    gcc
    clang
    readline
	lldb_18
    valgrind
	python3
   ];
}
