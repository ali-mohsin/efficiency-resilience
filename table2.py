import matplotlib.pyplot as plt
arr=[10987387,1787184,16780835,16908916,8498791,6063403,16804833,16645390,29137589,24906439,20309375,25001436,28804358,28605382,2311324,29690257,23660347,23329957,24307603,4669806,27341476,2750486,17550171,19421113,96250,28812986,26471043,26788373,29591443,5569478,21777485,7242972,26924307,18484271,29121674,6391283,1203208,2792099,12983649,14865365,549705,9512201,26646333,4511306,20550623,4747867,17158065,11206970,16049052,10945654,15075338,27328786,1592498,8436809,21990353,19374759,17189172,19560806,220238,22589634,29185600,15615322,16877396,12942389,21546238,13129880,23741333,17932827,18128608,22426331,14704514,15175372,18237106,15729191,23840995,21744558,689031,21886613,4182172,3009229,11233398,27382691,21630479,25341267,24201506,2394401,24601392,10799706,4822303,1295843,12396780,4206246,400281,13168591,13438213,25343568,27349633,24679048,20558130,11255552,20304266,6182009,13736078,27744157,21059670,12254384,4596753,16542261,12553489,4612191,10921377,15696019,17714724,9767476,12911734,5548843,29705686,638011,11228921,27032850,22454872,5745041,25747865,27081363,17030859,29325762,26682018,6223248,20429552,5185949,2046456,1589991,18369655,10050254,10895461,15823574,23514601,22391096,1132092,15772160,2415028,12043554,22074650,26883064,2402803,2575118,23372989,23875053,28723131,14851028,6668527,19715379,11546964,1263883,16993832,5222718,22647442,14934072,25346365,8998042,7118143,15089575,29707776,24750129,25406288,3082204,22792111,14774296,4904058,29534483,28106927,6339455,17056177,13025518,28123368,10151711,16113074,5732644,16722267,26768109,22600282,9236075,22647896,2247820,5081255,14482549,19055856,18975255,19644588,18514576,6540687,5525819,6423927,20990963,6773940,307454,125738,27282967,28586604,27874645,13829442,1888745,28211903,21513684,5381127,18140799,21210900,17091927,17441434,28330078,3391018,6105949,3213765,21323095,15436056,500933,14071287,14667149,23253679,25172386,16209094,5589324,2012509,12603878,8313197,26185670,22087840,27737324,713241,9618326,3290864,27931148,12508938,24678046,1295483,11946480,28196323,19957276,24198193,29352499,20357549,20276052,14956737,25249767,3633431,20638755,23795592,21263630,28843500,27134475,5295586,7849381,19856102,15914973,9996603,22027554,28146740,6061005,24154364,21129567,10225949,9253655,2884068,8254237,22837197,25546899,2420834,21029464,25754213,18847584,17244614,13654025,18211449,28494832,3542155,5186313,26425425,25338702,9989957,13553413,4014355,25992642,25012945,11228478,6482895,4067031,5983905,9118864,19952439,14110223,4787151,2295402,16252857,13038422,13743396,11586321,5692149,6709293,7117421,29021309,13046538,7327827,20809397,20774853,1609444,16772782,6697965,7609172,11734994,1709990,29755783,8268846,15907979,13702082,27948615,19142069,15811733,7574652,7949292,12415671,15750934,28471683,13289342,10432426,21761155,3019079,20471432,21997574,8782417,11921163,939400,12758890,10049481,18404968,1199400,22590213,12525444,21915586,22175457,3355475,9523133,17969902,178832,1406680,28183484,10724986,26907428,28390370,26333772,7472035,12648681,26999859,3640498,3505265,16296161,22268919,8267999,8330211,15239001,12440784,5581087,7578074,29166000,21961777,17796487,5549296,24528766,8135647,16497304,6501571,13534356,28612760,4042015,12765538,11712567,27736205,888446,14814874,23799077,8070570,1243168,24557085,23718078,18973902,26849996,13008848,19278667,14703060,26113637,20150754,22674922,2668915,5717592,6134166,19293144,23628585,5373658,11340951,3394755,9307119,8306679,23145457,28970280,15938733,5317116,27942826,6492800,16588110,611882,6759765,14476068,5474043,1090373,18941463,29646201,17246233,15597254,570931,18240207,4684156,17631857,29098418,28271427,1367753,3441509,13821039,21032220,20283657]
#arr=[8322162,1792541,27567328,7512918,426030,5169970,21441776,18389001,5399168,15873813,29381752,7574193,27276122,371236,24874281,14497208,10461537,23154358,28871837,24248846,9186504,20666330,5930906,9567077,13614629,7144576,21701229,10520513,2463105,17348812,20198018,3733949,1261508,12826286,3300154,11285137,8789036,22865842,17505372,22273366,17541129,25229004,58239,22540215,29157618,7407787,6767751,2531543,8030044,20678956,17465667,18849561,28948265,6007350,21697378,89990,22731362,997217,26101215,2860003,15942811,14614470,21409527,25772525,27536547,5802474,9102688,1485747,17112475,2616867,18853267,28600734,29471211,11342545,6371675,2229022,8252076,20053406,22235411,24464450,14207338,4870290,14268774,7659126,15433247,26379293,7983704,8086988,3318503,20825121,6557712,6907417,8747336,27310300,2768570,24579159,884832,10285936,13354544,24083912,5770112,28107009,27959584,16241436,8139883,23484618,12637052,24540088,9869210,17399840,8657843,29613689,6461154,19728986,5393744,13636193,16792456,24917673,12969904,8217874,23140294,5259539,21891912,21288327,15592590,16368546,11164468,23823013,27851192,15165340,6656728,632352,24302914,15111473,8266074,528468,14477353,12610630,4031825,24206386,8593747,11342538,6124460,738008,20679519,11278077,15353959,5088423,20772481,17894887,13529244,25477627,19244066,29408566,24503567,7933012,16706238,5371881,6957453,9322702,17045942,7489572,15027561,24573127,2777891,29871301,25924073,9346437,15953539,8444032,14886309,8587125,18168946,6939597,15101600,5279723,19379430,29580149,25347290,5239738,1653995,9465022,25492673,12746208,10082815,4419670,2599988,26561671,9482154,28411685,2279919,9247649,11493408,3615398,15497427,29998585,8998880,27245842,23307770,15937765,8731347,10876062,15880583,14616622,23455354,14979196,11752421,12427328,28087348,25119232,19930566,25768901,29614128,15937352]
arr.sort()
weeks=[0]*12
for i in arr:
    weeks[i/(30*24*60*60)]+=1

plt.bar(range(len(weeks)),weeks)
plt.xlabel("Month of the year")
plt.ylabel("Frequency of devices that will become failure prone")
plt.title("Distribution of Failure Start Times")
plt.show()