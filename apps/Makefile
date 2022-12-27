apps:
	make -C test 	&& cp test/test.app .
	make -C order 	&& cp order/order.app .

clean:
	rm -f *.app
	make -C test clean
	make -C order clean

.PHONY: clean
