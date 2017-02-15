#Test resistance lib
echo "Running tests of libresistance" && \
make -C lib/libresistance test && \

#Test power lib
echo "Running tests of power" && \
make -C lib/libpower test && \

#Test component lib
echo "Running tests of libcomponent" && \
make -C lib/libcomponent test && \

#Test full program
echo "Running regular make" && \
make && \

echo "Running make lib make" && \
make lib && \

echo "Testing installation make" && \
make install && \

echo "Testing uninstall make" && \
make uninstall

