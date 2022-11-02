
all:
	gcc src/* -o bin/ush

install:
	install bin/ush /usr/bin/ush

clean:
	rm bin/ush
