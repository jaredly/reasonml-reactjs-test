build:
	clear
	`npm bin`/bsc -pp refmt -impl src/moduledreact.re 2>&1 | huh

hello:
	./node_modules/.bin/bsc -pp refmt -impl Hello.re -bs-files *.ml *.mli 2>&1 | huh

amodule.js:
	./node_modules/.bin/bsc -impl amodule.ml -bs-files amodule.mli 2>&1 | huh

mod:
	./node_modules/.bin/bsc -c *.mli

.PHONY: build
