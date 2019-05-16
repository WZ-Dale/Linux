src = $(wildcard ./*.c)
obj = $(patsubst %.c, %.o, $(src))
bin = ./a
.PHONY: $(bin) clean 
$(bin) : $(obj)
	gcc $^ -o $@
%.o : %.c
	gcc -c $^ -o $@

clean:
	rm -rf $(obj) $(bin)
