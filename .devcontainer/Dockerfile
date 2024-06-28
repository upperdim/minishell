FROM mcr.microsoft.com/devcontainers/base:alpine-3.20

# Installieren Sie Pakete
RUN apk update && apk add --no-cache\
    git \
    vim \
    curl \
    valgrind \
    readline-dev\
    py3-setuptools;\
    python3 -m venv /home/.venv;\
    . /home/.venv/bin/activate;\
    pip install norminette;\
    deactivate;

ENV PATH="${PATH}:/home/.venv/bin"