FROM ubuntu:latest
LABEL authors="cjh"

ENTRYPOINT ["top", "-b"]