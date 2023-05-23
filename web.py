import requests
from bs4 import BeautifulSoup
import datetime

# set the URL and headers
url = 'https://www.google.com/search?q=除濕機+日立&rlz=1C1GCEU_zh-TWTW951TW951&tbs=cdr:1,cd_min:1/1/2023,cd_max:3/31/2023&sxsrf=ALiCzsZYSSrZV1HXKuyRrpo9TJd6iBzD0A:1651193551426&source=lnt&tbm=nws'
headers = {'User-Agent': 'Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/58.0.3029.110 Safari/537.3'}

# send request to the URL with headers
response = requests.get(url, headers=headers)

# parse the HTML content using Beautiful Soup
soup = BeautifulSoup(response.content, 'html.parser')

# find all the news articles in the HTML content
articles = soup.find_all('div', {'class': 'g'})

# iterate over each article and extract the relevant information
for article in articles:
    title = article.find('div', {'class': 'JheGif nDgy9d'}).text.strip()
    link = article.find('a')['href']
    source = article.find('div', {'class': 'XTjFC WF4CUc'}).text.strip()
    date_str = article.find('span', {'class': 'WG9SHc'}).text.strip().replace('年', '-').replace('月', '-').replace('日', '')
    date = datetime.datetime.strptime(date_str, '%Y-%m-%d').date()
    
    # check if the article is within the specified date range
    if date >= datetime.date(2023, 1, 1) and date <= datetime.date(2023, 3, 31):
        # check if the article is related to "除濕機" and "日立"
        if '除濕機' in title and '日立' in title:
            print('Title:', title)
            print('Link:', link)
            print('Source:', source)
            print('Date:', date)
            print('----------------------------------')