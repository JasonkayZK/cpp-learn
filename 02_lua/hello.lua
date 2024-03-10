-- Load the dynamic library
local lib = require("libtestlib")

avg, sum = lib.average(100, 200, 300, 400, 500)

diff = lib.sub(100,50)
total = lib.add(100,50)

print("Average is:" ..avg)
print("Sum is: " ..sum)

print("diff = "..diff)
print("total = "..total)
