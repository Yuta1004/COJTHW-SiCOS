apps:
	make -C test 	&& cp test/test.app .
	make -C order 	&& cp order/order.app .
	make -C fib 	&& cp fib/fib.app .
	make -C ball 	&& cp ball/ball.app .

clean:
	rm -f *.app
	make -C test clean
	make -C order clean
	make -C fib clean
	make -C ball clean

.PHONY: clean
