"""Browser regression for the workspace. Driven by TestWorkspaceBrowser."""
import json
import socket
import subprocess
import sys
import time
import urllib.error
import urllib.request

server = sys.argv[1]
with socket.socket() as port:
    port.bind(("127.0.0.1", 0))
    driver_port = port.getsockname()[1]
base = f"http://127.0.0.1:{driver_port}"

def call(method, path, body=None):
    request = urllib.request.Request(base + path, method=method,
        data=None if body is None else json.dumps(body).encode(),
        headers={"Content-Type": "application/json"})
    with urllib.request.urlopen(request, timeout=25) as response:
        return json.load(response)["value"]

def wait_for(check):
    deadline = time.monotonic() + 20
    while time.monotonic() < deadline:
        if check():
            return
        time.sleep(.1)
    raise AssertionError("Browser did not reach the expected state")

driver = subprocess.Popen(["chromedriver", f"--port={driver_port}"], stdout=subprocess.DEVNULL)
session = None
try:
    def ready():
        try:
            return call("GET", "/status")["ready"]
        except urllib.error.URLError:
            return False
    wait_for(ready)
    settings = {"browserName":"chrome", "goog:chromeOptions":{"args":["--headless", "--disable-dev-shm-usage"]}}
    session = "/session/" + call("POST", "/session", {"capabilities":{"alwaysMatch":settings}})["sessionId"]
    def script(js):
        return call("POST", session + "/execute/sync", {"script":js, "args":[]})
    def enter(selector):
        element = call("POST", session + "/element", {"using":"css selector","value":selector})
        eid = next(iter(element.values()))
        call("POST", session + "/element/" + eid + "/value", {"text":"\ue007"})
    key = "?id=Binary_Search/last-occurrence"
    call("POST", session + "/url", {"url":server+"/task"+key})
    script("const b=document.querySelector('#code');b.focus();b.value='    if (x) {}';b.setSelectionRange(12,12);")
    enter("#code")
    assert script("return document.querySelector('#code').value") == "    if (x) {\n        \n    }"
    script("const s=document.querySelector('#load-sample');s.value='0';s.dispatchEvent(new Event('change'));")
    assert script("return document.querySelector('[name=compare]').checked && document.querySelector('[name=stdin]').value.startsWith('7 5')")
    script("document.querySelector('#code').value='int main(){}';document.querySelector('[value=run]').click();")
    wait_for(lambda: script("return !document.querySelector('#code').form.hasAttribute('aria-busy')"))
    result = script("return document.querySelector('#trial-output').textContent")
    assert 'Output differs' in result, result
    assert script("return document.querySelector('#code').value") == "int main(){}"
    call("POST", session + "/url", {"url":server+"/editorial"+key})
    assert script("return document.querySelectorAll('#editorial h3').length") == 4
    assert script("return !!document.querySelector('#editorial pre .token.keyword')")
finally:
    try:
        if session:
            call("DELETE", session)
    finally:
        driver.terminate()
        driver.wait(timeout=5)
