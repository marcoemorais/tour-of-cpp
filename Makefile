PWD=$(shell pwd)
NAME=$(shell basename $(PWD))
IMAGE=$(NAME)
TAG=local
ACTION?=test

DIRS := \
    01-the-basics \
    02-user-defined-types \
    03-modularity \
    04-classes \
    05-essential-operations \
	06-templates \
    07-concepts-and-generic-programming \
	08-library-overview \
	09-strings-and-regular-expressions \
	10-input-and-output \
	11-containers \
	12-algorithms \
	13-utilities \
	14-numerics \
	15-concurrency

.PHONY: $(DIRS)

all:: $(DIRS)

$(DIRS):
	$(MAKE) -C $@ $(ACTION)

.PHONY: readme advice cp-vimrc

readme:
	docker run --name $(NAME) --rm -it -v $(PWD):/src $(IMAGE):$(TAG) pandoc --to html --metadata pagetitle=README --standalone README.md --output README.html

advice:
	docker run --name $(NAME) --rm -it -v $(PWD):/src $(IMAGE):$(TAG) pandoc --to html --metadata pagetitle=ADVICE --standalone ADVICE.md --output ADVICE.html

cp-vimrc:
	docker cp vimrc $(NAME):/root/.vimrc

include Makefile.defs
