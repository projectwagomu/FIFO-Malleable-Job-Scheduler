# Compiling the malleable APGAS library and the lifeline-based global load balancer
cd apgas
git submodule init
git submodule update
git checkout v0.0.1
mvn install -DskipTests
cd ../lifelineglb
git submodule init
git submodule update
git checkout v0.0.1
mvn package

