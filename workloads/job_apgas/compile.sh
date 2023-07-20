# Compiling the malleable APGAS library and the lifeline-based global load balancer
cd apgas
git checkout v0.0.1
mvn install -DskipTests
cd ../lifelineglb
git checkout v0.0.1
mvn package

