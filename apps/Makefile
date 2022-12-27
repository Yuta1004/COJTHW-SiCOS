apps:
	make -C test 	&& cp test/test.app .
	make -C order 	&& cp order/order.app .
	make -C fib 	&& cp fib/fib.app .

clean:
	rm -f *.app
	make -C test clean
	make -C order clean
	make -C fib clean

.PHONY: clean
