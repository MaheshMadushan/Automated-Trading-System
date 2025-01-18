# Building the project
`mkdir build && cd build && cmake .. && make`

# Running ATS after the build
`cd build && ./ats`

# Running tests
`cd build && ./run_tests`

`
Defining life of an order and trade

order -> matching engine -> *process -> order not matched -> put all/remaining on the order book
                            |                                           A
                            v                                           |
                            order matched -> partially fullfilled -------
                            |                       |
                            v                       |
                            fullfilled              | (async)
                            |                       |
                            v             (async)   v
                            trade done ---------> post trade activities (async)
                            |
                            v
                            update order book

`