apps:
	make -C test 	&& cp test/test.app .
	make -C order 	&& cp order/order.app .
	make -C fib 	&& cp fib/fibn.app .
	make -C ball 	&& cp ball/ball.app .
	make -C imball 	&& cp imball/imball.app .
	make -C count 	&& cp count/count.app .
	make -C echo 	&& cp echo/echo.app .
	make -C music 	&& cp music/music.app .
	make -C image 	&& cp image/image.app .

clean:
	rm -f *.app
	make -C test clean
	make -C order clean
	make -C fib clean
	make -C ball clean
	make -C imball clean
	make -C count clean
	make -C echo clean
	make -C music clean
	make -C image clean

.PHONY: clean
