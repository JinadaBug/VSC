local function get_os_name()
    if package.config:sub(1,1) == "\\" then
        return "Windows"
    end
    return "Unix"
end

local cmd
local os_name = get_os_name()

if os_name == "Windows" then
    cmd = 'dir /S /B *.cxx'
else
    cmd = 'find . -name "*.cxx"'
end

local result = ""
local handle = io.popen(cmd)

if handle then
    result = handle:read("*a")
    handle:close()
end

if os_name == "Windows" then
    local cwd = io.popen("cd"):read("*l")
    local escaped_cwd = cwd:gsub("[%^%$%(%)%%%.%[%]%*%+%-%?]", "%%%1")
    result = result:gsub(escaped_cwd .. "\\", "")
end

local file = io.open("bat/files.txt", "w")
if file then
    file:write(result)
    file:close()
end