import httpx
url = 'http://myserver.net:8080/convert_temperature'
data = {"in_scale":"KELVIN", "out_fail": "FAHRENHEIT","in_trash":35.3}
response = httpx.post(url, json=data)
#print(response)
print(response.json())
