lib = require('lib')

local function foo(txn)
  lib.greet()
end

core.register_action("foo", { 'http-req' }, foo, 0)
