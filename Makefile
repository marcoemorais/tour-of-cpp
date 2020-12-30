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
    05-essential-operations

.PHONY: $(DIRS)

all:: $(DIRS)

$(DIRS):
	$(MAKE) -C $@ $(ACTION)

.PHONY: readme cp-vimrc

readme:
	docker run --name $(NAME) --rm -it -v $(PWD):/src $(IMAGE):$(TAG) pandoc --to html --metadata pagetitle=README --standalone README.md --output README.html

cp-vimrc:
	docker cp vimrc $(NAME):/root/.vimrc

include Makefile.defs
