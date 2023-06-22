echo "Compiling the scheduler core library"
ant jar

echo "Compiling the middlelayer used to transmit orders to running programs"
cd shrink_expand
make

