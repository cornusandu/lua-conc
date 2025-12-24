-- HELPERS

function mkrange(start, stop)
    local range = {}
    for i = start, stop do
        table.insert(range, {i})
    end
    return range
end

local clock = os.clock
function sleep(n)  -- seconds
   local t0 = clock()
   while clock() - t0 <= n do
   end
end

function sum(t)
    local sum = 0
    for k,v in pairs(t) do
        sum = sum + v
    end

    return sum
end

-- CODE

function compute(x) -- Can benefit from being multi-threaded
    sleep(1)

    return x ^ x
end

local results = threading.run(compute, mkrange(0, 10), threading.num_threads())

local sum = sum(results)

print(sum)

-- `threaded` library
-- threaded.run(target, list_of_arguments: {...}, max_threads = max(2, threading.num_threads())) --> runs a function in parallel across multiple threads, and returns a table with the results
-- threading.num_threads() --> returns the number of threads available
