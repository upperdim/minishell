FROM mcr.microsoft.com/devcontainers/base:alpine-3.20

# Installieren Sie Pakete
RUN apk update && apk add --no-cache\
    git \
    vim \
    curl \
    valgrind \
    readline-dev
RUN python3 -m venv $HOME/.venv;\
    source $HOME/.venv/bin/activate;\
    python3 -m pip install --upgrade pip setuptools;\
    python3 -m pip install norminette;\
    echo "export PATH=\$PATH:$HOME/.venv/bin" >> $HOME/.${SHELL##/bin/}rc;\
    deactivate