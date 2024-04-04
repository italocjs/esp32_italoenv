# FROM italocjs/track_env:latest

# # Copy a the actual code so we can run the build
# #COPY firmware/ /workspace/
# #WORKDIR /workspace

FROM ubuntu:latest

RUN apt-get update && apt-get install -y \
    python3 \
    python3-pip

RUN pip install platformio

RUN apt-get install -y doxygen

WORKDIR /app

CMD ["/bin/bash"]
