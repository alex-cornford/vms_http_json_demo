#
# Example rest client using python and flask
#
import httpx
url = 'http://mysqrver.net:8080/convert_temperature'
data = {"in_scale":"CELSIUS","out_scale":"FAHRENHEIT","in_temperature":35.35}
response = httpx.post(url, json=data)
print(response.json())

