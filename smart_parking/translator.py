import os

import onnx

import tvm

import sys

import numpy as np



from tvm import relay, runtime

from tvm.relay import mera

from tvm.relay.mera import drp

from tvm.contrib import graph_executor

from google.protobuf.json_format import MessageToDict

from optparse import OptionParser

onnx_model = onnx.load_model("model.onnx")

input_node_name = "input"

input_shape     =[1,3,28,28]

shape_dict = {input_node_name:input_shape}

mod, params = relay.frontend.from_onnx(onnx_model, shape_dict)

drp_config_runtime = {

    "interpreter": False,

    "addr_map_start": 0x838E0000,

    "toolchain_dir": "/opt/drp-ai_translator_release",

    "sdk_root": "/opt/poky/3.1.17"

}

output_dir = "./parkingmodel_onnx"

# Run build operation of TVM backend

drp.build(mod, \

          params, \

         "arm", \

          drp_config_runtime, \

          output_dir=output_dir, \

          disable_concat = False

)

