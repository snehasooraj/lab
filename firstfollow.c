
#include <stdio.h>
#include <ctype.h>

int n;
char p[20][20], first[26][128], follow[26][128];

int main()
{
    int i,j,k,a,b,x,y,c,change,nullable;

    printf("Enter number of productions: ");
    scanf("%d",&n);

    printf("Enter productions:\n");
    for(i=0;i<n;i++)
        scanf("%s",p[i]);

    // FIRST
    do {
        change=0;
        for(i=0;i<n;i++) {
            a=p[i][0]-'A';
            nullable=1;

            for(j=2;p[i][j];j++) {
                b=p[i][j];

                if(b=='#') {
                    if(!first[a]['#'])
                        first[a]['#']=1,change=1;
                    break;
                }

                if(isupper(b)) {
                    x=b-'A';

                    for(k=0;k<128;k++)
                        if(first[x][k] && k!='#' && !first[a][k])
                            first[a][k]=1,change=1;

                    if(!first[x]['#']) {
                        nullable=0;
                        break;
                    }
                }
                else {
                    if(!first[a][b])
                        first[a][b]=1,change=1;
                    nullable=0;
                    break;
                }
            }

            if(nullable && !first[a]['#'])
                first[a]['#']=1,change=1;
        }
    } while(change);

    // FOLLOW
    follow[p[0][0]-'A']['$']=1;

    do {
        change=0;

        for(i=0;i<n;i++) {
            a=p[i][0]-'A';

            for(j=2;p[i][j];j++) {
                b=p[i][j];

                if(isupper(b)) {
                    x=b-'A';
                    nullable=1;

                    for(k=j+1;p[i][k];k++) {
                        if(isupper(p[i][k])) {
                            y=p[i][k]-'A';

                            for(c=0;c<128;c++)
                                if(first[y][c] && c!='#' && !follow[x][c])
                                    follow[x][c]=1,change=1;

                            if(!first[y]['#']) {
                                nullable=0;
                                break;
                            }
                        }
                        else {
                            if(!follow[x][p[i][k]])
                                follow[x][p[i][k]]=1,change=1;
                            nullable=0;
                            break;
                        }
                    }

                    if(nullable)
                        for(c=0;c<128;c++)
                            if(follow[a][c] && !follow[x][c])
                                follow[x][c]=1,change=1;
                }
            }
        }
    } while(change);

    // OUTPUT
    printf("\nFIRST:\n");

    for(i=0;i<n;i++) {
        a=p[i][0]-'A';

        if(i==0 || p[i][0]!=p[i-1][0]) {
            printf("FIRST(%c) = { ",p[i][0]);

            for(j=0;j<128;j++)
                if(first[a][j])
                    printf("%c ",j);

            printf("}\n");
        }
    }

    printf("\nFOLLOW:\n");

    for(i=0;i<n;i++) {
        a=p[i][0]-'A';

        if(i==0 || p[i][0]!=p[i-1][0]) {
            printf("FOLLOW(%c) = { ",p[i][0]);

            for(j=0;j<128;j++)
                if(follow[a][j])
                    printf("%c ",j);

            printf("}\n");
        }
    }

    return 0;
}
