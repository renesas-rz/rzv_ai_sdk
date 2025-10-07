#!/bin/bash

ENV_NAME="fish_web_app"

virtualenv "$ENV_NAME"

source "$ENV_NAME/bin/activate"

pip install -r requirements.txt



