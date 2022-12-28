apps:
	make -C test 	&& cp test/test.app .
	make -C order 	&& cp order/order.app .
	make -C fib 	&& cp fib/fibn.app .
	make -C ball 	&& cp ball/ball.app .
	make -C count 	&& cp count/count.app .

clean:
	rm -f *.app
	make -C test clean
	make -C order clean
	make -C fib clean
	make -C ball clean
	make -C count clean

.PHONY: clean
