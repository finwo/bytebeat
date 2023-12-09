TUNES=$(shell ls tunes)

.PHONY: default
default: $(TUNES)

$(TUNES):
	cd tunes/$@ && make
